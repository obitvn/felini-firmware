#include "AppInfosModel.h"
#include <stdio.h>

using namespace Page;

void AppInfosModel::Init()
{
    account = new Account("AppInfosModel", DataProc::Center(), 0, this);

    // account->Subscribe("SportStatus");
    // account->Subscribe("GPS");
    // account->Subscribe("MAG");
    // account->Subscribe("IMU");
    // account->Subscribe("Clock");
    // account->Subscribe("Power");
    // account->Subscribe("Storage");
    account->Subscribe("StatusBar");
}

void AppInfosModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void AppInfosModel::GetSportInfo(
    float* trip,
    char* time, uint32_t len,
    float* maxSpd
)
{
    
    *trip = 76;

    *maxSpd = 53;
    *time = 12;
}

void AppInfosModel::GetGPSInfo(
    float* lat,
    float* lng,
    float* alt,
    char* utc, uint32_t len,
    float* course,
    float* speed
)
{

    *lat = 13;
    *lng = 443;
    *alt = 23;

    utc[0] = '3';

    *course = 4;
    *speed = 12;
}

void AppInfosModel::GetMAGInfo(
    float* dir,
    int* x,
    int* y,
    int* z
)
{


    *dir = 0;
    *x = 23;
    *y = 87;
    *z = 134;
}

void AppInfosModel::GetIMUInfo(
    int* step,
    char* info, uint32_t len
)
{

    *step = 128;
    info[0] = '1';

}

void AppInfosModel::GetRTCInfo(
    char* dateTime, uint32_t len
)
{
    dateTime[0] = '2';

}

void AppInfosModel::GetBatteryInfo(
    int* usage,
    float* voltage,
    char* state, uint32_t len
)
{
    *usage =37;
    *voltage = 3789 / 1000.0f;
    state[0] = '8';
}

void AppInfosModel::GetStorageInfo(
    bool* detect,
    const char** type,
    char* usage, uint32_t len
)
{
    *detect = 1;
    *type = "qưewqeqw";
    usage[0] = 'o';


}

void AppInfosModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}
