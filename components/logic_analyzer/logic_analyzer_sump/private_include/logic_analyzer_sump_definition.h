#pragma once
// definition esp32s3
// 43-tx 44-rx
// definition esp32c3
// 21-tx 20-rx
// sigrok default sample rate
#define PULSEVIEW_MAX_SAMPLE_RATE 100000000

// define uart port - default port
#ifdef CONFIG_ANALYZER_USE_SUMP

#define SUMP_UART_PORT_NUM CONFIG_ANALYZER_SUMP_UART_PORT_NUMBER
#define SUMP_TEST_TXD CONFIG_ANALYZER_SUMP_UART_PORT_TX_PIN
#define SUMP_TEST_RXD CONFIG_ANALYZER_SUMP_UART_PORT_RX_PIN
#define SUMP_UART_BAUD_RATE CONFIG_ANALYZER_SUMP_UART_PORT_BAUD_RATE

#else

#define SUMP_UART_PORT_NUM 0
#define SUMP_TEST_TXD 1
#define SUMP_TEST_RXD 3
#define SUMP_UART_BAUD_RATE 921600

#endif

#define SUMP_TEST_RTS (UART_PIN_NO_CHANGE)
#define SUMP_TEST_CTS (UART_PIN_NO_CHANGE)

#define UART_BUF_SIZE (2048)

/*
 *  SUMP COMMAND DEFINITION
 */

/* XON/XOFF are not supported. */
#define SUMP_RESET 0x00
#define SUMP_ARM 0x01
#define SUMP_QUERY 0x02
#define SUMP_XON 0x11
#define SUMP_XOFF 0x13

/* mask & values used, config ignored. only stage0 supported */
#define SUMP_TRIGGER_MASK_CH_A 0xC0
#define SUMP_TRIGGER_MASK_CH_B 0xC4
#define SUMP_TRIGGER_MASK_CH_C 0xC8
#define SUMP_TRIGGER_MASK_CH_D 0xCC

#define SUMP_TRIGGER_VALUES_CH_A 0xC1
#define SUMP_TRIGGER_VALUES_CH_B 0xC5
#define SUMP_TRIGGER_VALUES_CH_C 0xC9
#define SUMP_TRIGGER_VALUES_CH_D 0xCD

#define SUMP_TRIGGER_CONFIG_CH_A 0xC2
#define SUMP_TRIGGER_CONFIG_CH_B 0xC6
#define SUMP_TRIGGER_CONFIG_CH_C 0xCA
#define SUMP_TRIGGER_CONFIG_CH_D 0xCE

/* Most flags are ignored. */
#define SUMP_SET_DIVIDER 0x80
#define SUMP_SET_READ_DELAY_COUNT 0x81
#define SUMP_SET_FLAGS 0x82
#define SUMP_SET_BIG_READ_CNT 0x83

// 84 - f9 1000
// 83 - f9 1000
// #define SUMP_SET_RLE 0x0100

/* extended commands -- self-test unsupported, but metadata is returned. */
#define SUMP_SELF_TEST 0x03
#define SUMP_GET_METADATA 0x04
