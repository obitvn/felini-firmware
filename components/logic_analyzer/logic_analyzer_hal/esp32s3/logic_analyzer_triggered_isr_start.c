/* logic analyzer ll example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
/*
 * standart irq handlers too slow >2.5 mks
 * hi level 5 irq about 0.3 mks то start transfer
 */

// #include "soc/dport_reg.h"
#include "soc/interrupt_reg.h"
#include "soc/gpio_reg.h"
#include "soc/soc.h"
#include "rom/ets_sys.h"
#include "logic_analyzer_ll.h"
#include "logic_analyzer_hi_level_interrupt.h"
#include "esp_log.h"

hi_interrupt_state_t la_hi_interrupt_state;
static int hi_interrupt_started = 0;
// reset hi level int to default mode
void ll_hi_level_triggered_isr_timeout_stop(void)
{
#ifdef CONFIG_ANALYZER_USE_HI_LEVEL_INTERRUPT
    if (hi_interrupt_started)
    {
        // disable interrupt on core
        _DPORT_REG_WRITE(la_hi_interrupt_state.dport_int_map_reg, la_hi_interrupt_state.dport_int_map_data_disable);
        // clear GPIO interrupt enable on core // restore cfg register
        REG_WRITE(la_hi_interrupt_state.gpio_pin_cfg_reg, la_hi_interrupt_state.gpio_pin_cfg_backup_data);
        hi_interrupt_started = 0;
    }
#endif
}
// allocate hi level int level5, save GPIO & IRQ regs, start irq
void ll_triggered_isr_alloc(void *arg)
{
    ESP_LOGD("AISR", "start");

    // for shared interrupt (gpio pin interrupt defined on both cores )  ( simultaneously on 2 cores )
    // if interrupt edge predefined and interrupt enable on core
    // interrupt edge not change ???
    uint32_t trigger_edge = (uint32_t)arg;
    la_hi_interrupt_state.gpio_pin_cfg_trig_data = 0;
    la_hi_interrupt_state.gpio_pin_cfg_backup_data = REG_READ(la_hi_interrupt_state.gpio_pin_cfg_reg);
    uint32_t tmp_trig = (la_hi_interrupt_state.gpio_pin_cfg_backup_data >> 7) & 0x7;
    if (tmp_trig == 0 || (la_hi_interrupt_state.gpio_pin_cfg_backup_data & (0x1 << 13)) == 0)
    {
        tmp_trig = trigger_edge;
    }
    la_hi_interrupt_state.gpio_pin_cfg_trig_data = (tmp_trig << 7) | la_hi_interrupt_state.gpio_pin_cfg_int_ena_core_bit;

    ESP_INTR_DISABLE(HI_INTERRUPT_NUMBER);

    REG_WRITE(la_hi_interrupt_state.gpio_pin_cfg_reg, 0);                                  // todo clear only int bits       // disable all interrupt on GPIO
    REG_WRITE(la_hi_interrupt_state.gpio_stat_clr_reg, la_hi_interrupt_state.gpio_mask);   // clear intr status
    intr_matrix_set(la_hi_interrupt_state.cpu, ETS_GPIO_INTR_SOURCE, HI_INTERRUPT_NUMBER); // route gpio interrupt on hi-level int

    ESP_INTR_ENABLE(HI_INTERRUPT_NUMBER);

    REG_WRITE(la_hi_interrupt_state.gpio_stat_clr_reg, la_hi_interrupt_state.gpio_mask);             // clear intr status
    REG_WRITE(la_hi_interrupt_state.gpio_pin_cfg_reg, la_hi_interrupt_state.gpio_pin_cfg_trig_data); // enable GPIO interrupt on hi-level core

    vTaskDelete(NULL);
}
// start hi level int, determine low level/hi level, number of free core IRQ, fill state struct for asm irq handler
void ll_hi_level_triggered_isr_start(int pin_trigger, int trigger_edge)
{
    int int_free_pro = 0;
    int int_free_app = 0;
    if (pin_trigger < 0)
        return;
    la_hi_interrupt_state.cpu = 2;
    switch (_DPORT_REG_READ(INTERRUPT_CORE0_GPIO_INTERRUPT_PRO_MAP_REG))
    {
    case 6:
    case 7:
    case 11:
    case 15:
    case 16:
    case 29:
        int_free_pro = 1;
        la_hi_interrupt_state.cpu = 0; // use hi-level int on pro cpu (0)
        break;
    default:
        int_free_pro = 0;
        break;
    }
    switch (_DPORT_REG_READ(INTERRUPT_CORE1_GPIO_INTERRUPT_PRO_MAP_REG))
    {
    case 6:
    case 7:
    case 11:
    case 15:
    case 16:
    case 29:
        int_free_app = 1;
        la_hi_interrupt_state.cpu = 1; // use hi-level int on app cpu (1)
        break;
    default:
        int_free_app = 0;
        break;
    }

    ESP_LOGD("TISR", "pro=%ld app=%ld cpu=%ld", _DPORT_REG_READ(INTERRUPT_CORE0_GPIO_INTERRUPT_PRO_MAP_REG), _DPORT_REG_READ(INTERRUPT_CORE1_GPIO_INTERRUPT_PRO_MAP_REG), la_hi_interrupt_state.cpu);

    if ((int_free_app | int_free_pro) == 0) // all gpio int ( app&pro ) predefined - slow gpio int
    {
        ESP_LOGI("TISR", "slow gpio interrupt");
        gpio_install_isr_service(0); // default
        gpio_set_intr_type(pin_trigger, trigger_edge);
        gpio_isr_handler_add(pin_trigger, la_ll_trigger_isr, (void *)pin_trigger);
        gpio_intr_disable(pin_trigger);
        gpio_intr_enable(pin_trigger);
        return;
    }
    else
    {
        ESP_LOGD("TISR", "fast gpio interrupt");
        hi_interrupt_started = 1;
        la_hi_interrupt_state.dport_int_map_data_disable = 6;                                                                                                                 // soft interrupt - disable gpio interrupt
        la_hi_interrupt_state.dport_int_map_reg = (la_hi_interrupt_state.cpu == 0) ? INTERRUPT_CORE0_GPIO_INTERRUPT_PRO_MAP_REG : INTERRUPT_CORE1_GPIO_INTERRUPT_PRO_MAP_REG; // app/pro map register
        la_hi_interrupt_state.dport_int_stat_reg = (la_hi_interrupt_state.cpu == 0) ? INTERRUPT_CORE0_INTR_STATUS_0_REG : INTERRUPT_CORE1_INTR_STATUS_0_REG;                  // not used now // app/pro int status dport register
        la_hi_interrupt_state.gpio_mask = (pin_trigger < 32) ? 1 << pin_trigger : 1 << (pin_trigger - 32);                                                                    // hi/low interupt mask ( 0-31 )( 32-39 )
        la_hi_interrupt_state.gpio_stat_reg = (pin_trigger < 32) ? GPIO_STATUS_REG : GPIO_STATUS1_REG;                                                                        // not used now // hi/low interupt status register ( 0-31 )( 32-39 )
        la_hi_interrupt_state.gpio_stat_clr_reg = (pin_trigger < 32) ? GPIO_STATUS_W1TC_REG : GPIO_STATUS1_W1TC_REG;                                                          // hi/low interupt status clear register ( 0-31 )( 32-39 )
        la_hi_interrupt_state.gpio_pin_cfg_reg = GPIO_PIN0_REG + (4 * pin_trigger);                                                                                           // gpio config register corresponded with trigger pin
        la_hi_interrupt_state.gpio_pin_cfg_int_ena_core_bit = (la_hi_interrupt_state.cpu == 0) ? (1 << 13) : (1 << 13);                                                       // app/pro enable interrupt in cfg gpio register - 0 for fast clear

        la_hi_interrupt_state.i2s_set_vsync_reg = GPIO_FUNC152_IN_SEL_CFG_REG; // i2s0/i2s1
        la_hi_interrupt_state.i2s_set_vsync_bit = HI_INTERRUPT_SET_VSYNC;

        // alloc hi level int on free core
        xTaskCreatePinnedToCore(ll_triggered_isr_alloc, "trigg_alloc", 4096, (void *)trigger_edge, 20, NULL, la_hi_interrupt_state.cpu);
    }
}
