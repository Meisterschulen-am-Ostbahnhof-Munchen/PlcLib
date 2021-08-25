/*
 * TimeLib.cpp
 *
 *  Created on: 24.08.2021
 *      Author: FranzHoepfinger
 */


#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"


#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"


int32_t T_PLC_MS(void) // @suppress("Name convention for function")
{
	return (esp_log_timestamp());
}
