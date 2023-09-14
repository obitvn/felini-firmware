#pragma once
//
// used on hi level interrupt
//
#ifdef __cplusplus
extern "C"
{
#endif
    void la_ll_trigger_isr(void *pin);
    // define register and const to extra speed and simple asm handler
    typedef struct hi_interrupt_state
    {
        uint32_t cpu;
        uint32_t dport_int_map_reg;             // pro?app dport_reg - int31
        uint32_t dport_int_map_data_disable;    // route to int6
        uint32_t dport_int_stat_reg;            // pro?app dport_reg - source22
        uint32_t gpio_mask;                     // pin mask  ->  0 - may be shared( pro/app) ? bit mask (0-31) (32-39)
        uint32_t gpio_stat_reg;                 // gpio pin status reg (0-31) (32-39)
        uint32_t gpio_stat_clr_reg;             // gpio pin clear status reg (0-31) (32-39)
        uint32_t gpio_pin_cfg_reg;              // gpio pin config reg (0-39 )
        uint32_t gpio_pin_cfg_int_ena_core_bit; // pro ? app -  inverted for clr (~ena_bit)
        uint32_t gpio_pin_cfg_trig_data;        // pin cfg data for start irq
        uint32_t gpio_pin_cfg_backup_data;      // restore pin cfg data to default
        uint32_t i2s_set_vsync_reg;             // imux vsync reg i2s
        uint32_t i2s_set_vsync_bit;             // 0x38 - set bit
    } hi_interrupt_state_t;
// level 5 int route to core irq 31
#define HI_INTERRUPT_NUMBER 31
// const to set vsynk to hi level ->start transfer
#define HI_INTERRUPT_SET_VSYNC 0xb8

#ifdef __cplusplus
}
#endif
