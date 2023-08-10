#ifndef _DAP_MAIN_H_
#define _DAP_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

    int daplink_start(void);
    int daplink_stop(void);
    bool is_daplink_connect(void);
    bool is_daplink_running(void);

#ifdef __cplusplus
}
#endif

#endif