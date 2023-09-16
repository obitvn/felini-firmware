#ifndef _DAP_MAIN_H_
#define _DAP_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

    int daplink_start(void); // mode = 0 => only cdc
    int daplink_stop(void);
    bool is_daplink_connect(void);
    bool is_daplink_running(void);

    void cdc_uart_enable(bool mode);

#ifdef __cplusplus
}
#endif

#endif