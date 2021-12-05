/*
 * TimeLib.cpp
 *
 *  Created on: 24.08.2021
 *      Author: FranzHoepfinger
 */


#include <stdbool.h>
#include <stdint.h>
#include <time.h>       //used to get time for random number generator
#include "TimeLib.h"


#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"


int32_t T_PLC_MS(void) // @suppress("Name convention for function")
{
    return (esp_log_timestamp());
}


int32_t T_PLC_US(void) // @suppress("Name convention for function")
{

    struct timespec tv; //RAII complicated or impossible
    clock_gettime(CLOCK_MONOTONIC, &tv);
    return static_cast<int32_t>(((tv.tv_sec) * 1000 * 1000) + ((tv.tv_nsec) / 1000));
}
