//
// fake interrupt handler
// for create asm file
// /home/ok-home/.espressif/tools/xtensa-esp32-elf/esp-2022r1-11.2.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc /home/ok-home/myex/logic_analizer/logic_analyzer_hal/fake_hi_interrupt_s.c -S -O3

// header
/*
.data
_l5_intr_stack:
.space      16

    .section .iram1,"ax"
    .literal_position
    .literal .LC0, la_hi_interrupt_state
    .align	4
    .global	xt_highint5
    .type	xt_highint5, @function

xt_highint5:
//
    movi    a0,     _l5_intr_stack
    s32i    a8,     a0,     0
    s32i    a9,     a0,     4
    s32i    a10,    a0,     8
//	s32i    a11,    a0,     12

//  start of replacement block
*/

// footer
/*
//	end of replacement block

    movi    a0,     _l5_intr_stack
    l32i    a8,     a0,     0
    l32i    a9,     a0,     4
    l32i    a10,    a0,     8
//	l32i    a11,    a0,     12
//
    rsr.excsave5 a0
    rfi     5

.global la_include_hi_interrupt
la_include_hi_interrupt:
*/
//
#include <stdint.h>
#define _REG_READ(_r) (*(volatile uint32_t *)(_r))
#define _REG_WRITE(_r, _v) (*(volatile uint32_t *)(_r)) = (_v)

#include "./include/logic_analyzer_hi_level_interrupt.h"

extern hi_interrupt_state_t la_hi_interrupt_state;

void xt_highint5(void)
{
    // save reg
    //  default use int31

    // start of replacement block
    if (_REG_READ(la_hi_interrupt_state.gpio_stat_reg) & la_hi_interrupt_state.gpio_mask)
    {
        //  start dma - set vsync bit to 1
        _REG_WRITE(la_hi_interrupt_state.i2s_set_vsync_reg, la_hi_interrupt_state.i2s_set_vsync_bit);
        // disable interrupt on core
        _REG_WRITE(la_hi_interrupt_state.dport_int_map_reg, la_hi_interrupt_state.dport_int_map_data_disable);
        // clear GPIO interrupt enable on core - restore gpio cfg data
        _REG_WRITE(la_hi_interrupt_state.gpio_pin_cfg_reg, la_hi_interrupt_state.gpio_pin_cfg_backup_data);
        // clear interrupt status if not shared // not used now
        //_REG_WRITE(la_hi_interrupt_state.gpio_stat_clr_reg, la_hi_interrupt_state.gpio_mask);
    }
    //	end of replacement block

    // restore reg
    // iret
}
