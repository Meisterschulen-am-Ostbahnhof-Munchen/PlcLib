/*
 * AutomationTimer.cpp
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */



#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"
#include "Automation.h"
#include "AutomationTimer.h"


#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"

static const char *TAG = "AutomationTimer";

void THREE_POSITION_TOF::operator ()(void)
{

	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();


	// raising Edge
	if (M == THREE_POSITION_SWITCH_v1::Off)
	{
		if (OUT == THREE_POSITION_SWITCH_v1::Off)
		{
			if(IN == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right)
			{
				ESP_LOGD(TAG, "TOF_1: raising Edge detected Momentary_forward_up_right");
				//Start the Timer
				StartTime = tx;
			}

			if(IN == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left)
			{
				ESP_LOGD(TAG, "TOF_1: raising Edge detected Momentary_backward_down_left");
				//Start the Timer
				StartTime = tx;
			}
		}
		else //OUT = on, stop Timer.
		{
			if (IN != THREE_POSITION_SWITCH_v1::Off)
			{
				OUT = THREE_POSITION_SWITCH_v1::Off;
				IN  = THREE_POSITION_SWITCH_v1::Off;
			}
		}
	}


	if (IN != THREE_POSITION_SWITCH_v1::Off)
	{
		OUT = IN;
		ET = 0;
	}
	else
	{
		ET = tx - StartTime;
	}



	M = IN; //remember old State.

	ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);

	if (IN == THREE_POSITION_SWITCH_v1::Off)  //This FB is INPUT First Priority.
	{
		if (ET >= PT)
		{
			OUT = THREE_POSITION_SWITCH_v1::Off;
		}

		if (RST)
		{
			OUT = THREE_POSITION_SWITCH_v1::Off;
			RST = false;
		}
	}


}
