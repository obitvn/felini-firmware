#include "ServoCtrlModel.h"

using namespace Page;

void ServoCtrlModel::Init()
{
    account = new Account("RCServoModel", DataProc::Center(), 0, this);
    account->Subscribe("RCServoHardware");
    account->SetEventCallback(onEvent);

    HAL::RCServo_Info_t info_val;
    info_val.cmd = HAL::SERVO_CMD_INIT;
    info_val.angle = 0;
    info_val.mode = 0;
    account->Notify("RCServoHardware", &info_val, sizeof(info_val));
}

void ServoCtrlModel::Deinit()
{
    HAL::RCServo_Info_t info_val;
    info_val.cmd = HAL::SERVO_CMD_Deinit;
    info_val.angle = 0;
    info_val.mode = 0;
    account->Notify("RCServoHardware", &info_val, sizeof(info_val));
}

#include "stdio.h"
void ServoCtrlModel::ServoUpdateAngle(int16_t angle)
{
    HAL::RCServo_Info_t info_val;
    printf("angle %d\r\n", angle);
    info_val.cmd = HAL::SERVO_CMD_UPDATE;
    info_val.angle = angle;
    info_val.mode = 1;
    account->Notify("RCServoHardware", &info_val, sizeof(info_val));
    
}

int ServoCtrlModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}