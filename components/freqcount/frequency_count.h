
#pragma once
#ifndef FREQUENCY_COUNT_H
#define FREQUENCY_COUNT_H

#include <stdint.h>
#include "driver/pcnt.h"
#include "driver/rmt.h"

#ifdef __cplusplus
extern "C" {
#endif

    void frequency_init(void);
    void frequency_deinit(void);
    uint32_t frequency_hz(void);

#ifdef __cplusplus
}
#endif

#endif // FREQUENCY_COUNT
