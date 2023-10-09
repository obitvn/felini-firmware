#include "HertzModel.h"

using namespace Page;


using namespace Page;

void HertzModel::Init()
{
    account = new Account("HertzModel", DataProc::Center(), 0, this);
    account->Subscribe("RCServoHardware");
    account->SetEventCallback(onEvent);

    HAL::RCServo_Info_t info_val;
    info_val.cmd = HAL::SERVO_CMD_INIT;
    info_val.angle = 0;
    info_val.mode = 0;
    account->Notify("RCServoHardware", &info_val, sizeof(info_val));
}

void HertzModel::Deinit()
{
    HAL::RCServo_Info_t info_val;
    info_val.cmd = HAL::SERVO_CMD_Deinit;
    info_val.angle = 0;
    info_val.mode = 0;
    account->Notify("RCServoHardware", &info_val, sizeof(info_val));
}

#include "stdio.h"
void HertzModel::Update(uint32_t frequency, uint8_t duty)
{
    HAL::RCServo_Info_t info_val;
    info_val.cmd = HAL::SERVO_CMD_SETUP;
    info_val.frequency = frequency;
    info_val.duty = duty;
    info_val.mode = 1;
    printf("herzt set freq %ld, duty %d\n", frequency, duty);
    account->Notify("RCServoHardware", &info_val, sizeof(info_val));
}

int HertzModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}