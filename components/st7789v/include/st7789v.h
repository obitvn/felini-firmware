#ifndef __ST7789V_H__
#define __ST7789V_H__

#include <stdio.h>

#define ST7789V_HOR_RES (280)
#define ST7789V_VER_RES (240)

/* ST7789 commands */
#define ST7789V_NOP 0x00
#define ST7789V_SWRESET 0x01
#define ST7789V_RDDID 0x04
#define ST7789V_RDDST 0x09

#define ST7789V_RDDPM 0x0A       // Read display power mode
#define ST7789V_RDD_MADCTL 0x0B  // Read display MADCTL
#define ST7789V_RDD_COLMOD 0x0C  // Read display pixel format
#define ST7789V_RDDIM 0x0D       // Read display image mode
#define ST7789V_RDDSM 0x0E       // Read display signal mode
#define ST7789V_RDDSR 0x0F  // Read display self-diagnostic result (ST7789V)

#define ST7789V_SLPIN 0x10
#define ST7789V_SLPOUT 0x11
#define ST7789V_PTLON 0x12
#define ST7789V_NORON 0x13

#define ST7789V_INVOFF 0x20
#define ST7789V_INVON 0x21
#define ST7789V_GAMSET 0x26  // Gamma set
#define ST7789V_DISPOFF 0x28
#define ST7789V_DISPON 0x29
#define ST7789V_CASET 0x2A
#define ST7789V_RASET 0x2B
#define ST7789V_RAMWR 0x2C
#define ST7789V_RGBSET 0x2D  // Color setting for 4096, 64K and 262K colors
#define ST7789V_RAMRD 0x2E

#define ST7789V_PTLAR 0x30
#define ST7789V_VSCRDEF 0x33  // Vertical scrolling definition (ST7789V)
#define ST7789V_TEOFF 0x34    // Tearing effect line off
#define ST7789V_TEON 0x35     // Tearing effect line on
#define ST7789V_MADCTL 0x36   // Memory data access control
#define ST7789V_IDMOFF 0x38   // Idle mode off
#define ST7789V_IDMON 0x39    // Idle mode on
#define ST7789V_RAMWRC 0x3C   // Memory write continue (ST7789V)
#define ST7789V_RAMRDC 0x3E   // Memory read continue (ST7789V)
#define ST7789V_COLMOD 0x3A

#define ST7789V_RAMCTRL 0xB0    // RAM control
#define ST7789V_RGBCTRL 0xB1    // RGB control
#define ST7789V_PORCTRL 0xB2    // Porch control
#define ST7789V_FRCTRL1 0xB3    // Frame rate control
#define ST7789V_PARCTRL 0xB5    // Partial mode control
#define ST7789V_GCTRL 0xB7      // Gate control
#define ST7789V_GTADJ 0xB8      // Gate on timing adjustment
#define ST7789V_DGMEN 0xBA      // Digital gamma enable
#define ST7789V_VCOMS 0xBB      // VCOMS setting
#define ST7789V_LCMCTRL 0xC0    // LCM control
#define ST7789V_IDSET 0xC1      // ID setting
#define ST7789V_VDVVRHEN 0xC2   // VDV and VRH command enable
#define ST7789V_VRHS 0xC3       // VRH set
#define ST7789V_VDVSET 0xC4     // VDV setting
#define ST7789V_VCMOFSET 0xC5   // VCOMS offset set
#define ST7789V_FRCTR2 0xC6     // FR Control 2
#define ST7789V_CABCCTRL 0xC7   // CABC control
#define ST7789V_REGSEL1 0xC8    // Register value section 1
#define ST7789V_REGSEL2 0xCA    // Register value section 2
#define ST7789V_PWMFRSEL 0xCC   // PWM frequency selection
#define ST7789V_PWCTRL1 0xD0    // Power control 1
#define ST7789V_VAPVANEN 0xD2   // Enable VAP/VAN signal output
#define ST7789V_CMD2EN 0xDF     // Command 2 enable
#define ST7789V_PVGAMCTRL 0xE0  // Positive voltage gamma control
#define ST7789V_NVGAMCTRL 0xE1  // Negative voltage gamma control
#define ST7789V_DGMLUTR 0xE2    // Digital gamma look-up table for red
#define ST7789V_DGMLUTB 0xE3    // Digital gamma look-up table for blue
#define ST7789V_GATECTRL 0xE4   // Gate control
#define ST7789V_SPI2EN 0xE7     // SPI2 enable
#define ST7789V_PWCTRL2 0xE8    // Power control 2
#define ST7789V_EQCTRL 0xE9     // Equalize time control
#define ST7789V_PROMCTRL 0xEC   // Program control
#define ST7789V_PROMEN 0xFA     // Program mode enable
#define ST7789V_NVMSET 0xFC     // NVM setting
#define ST7789V_PROMACT 0xFE    // Program action

void st7789v_init(void);
void st7789v_backlight_set(uint16_t brightness);
void st7789v_flush(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2,
                   void *color_map);

#endif
