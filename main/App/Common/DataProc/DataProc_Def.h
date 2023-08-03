#ifndef __DATA_PROC_DEF_H
#define __DATA_PROC_DEF_H

#include <stdint.h>

namespace DataProc
{

    /* StatusBar */
    typedef enum
    {
        STATUS_BAR_STYLE_TRANSP,
        STATUS_BAR_STYLE_BLACK,
    } StatusBar_Style_t;

    typedef enum
    {
        STATUS_BAR_CMD_APPEAR,
        STATUS_BAR_CMD_SET_STYLE,
        STATUS_BAR_CMD_SET_LABEL_REC
    } StatusBar_Cmd_t;
    /* StatusBar */
    typedef struct
    {
        bool showLabelRec;
        const char *labelRecStr;
        StatusBar_Cmd_t cmd;
        union
        {
            bool appear;
            StatusBar_Style_t style;
            struct
            {
                bool show;
                const char *str;
            } labelRec;
        } param;
    } StatusBar_Info_t;

    

}

#endif
