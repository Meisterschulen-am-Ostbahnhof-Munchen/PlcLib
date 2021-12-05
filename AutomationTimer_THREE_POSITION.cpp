/*
 * AutomationTimer.cpp
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */



#include "AutomationTimer_THREE_POSITION.h"

#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"
#include "Automation.h"


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

static const char *TAG = "AutomationTimer";

void THREE_POSITION_TOF::operator ()(void)
{

	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	ET = tx - StartTime;
	ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);

	switch (IN){
	case THREE_POSITION_SWITCH_v1::Off:
		if (ET >= PT)
		{
			OUT = THREE_POSITION_SWITCH_v1::Off;
		}
		break;
	case THREE_POSITION_SWITCH_v1::Momentary_forward_up_right:
	case THREE_POSITION_SWITCH_v1::Momentary_backward_down_left:
		if (OUT != THREE_POSITION_SWITCH_v1::Off)
		{
			ESP_LOGD(TAG, "TOF_1: cancel detected");
			OUT = THREE_POSITION_SWITCH_v1::Off;
			IN  = THREE_POSITION_SWITCH_v1::Off;
		}
		else
		{
			ESP_LOGD(TAG, "TOF_1: raising Edge detected");
			//Start the Timer
			StartTime = tx;
			OUT = IN;
		}
		break;
	case THREE_POSITION_SWITCH_v1::held_forward_up_right:
		if (OUT == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right)
		{
			ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
			OUT = IN;
		}
		break;
	case THREE_POSITION_SWITCH_v1::held_backward_down_left:
		if (OUT == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left)
		{
			ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
			OUT = IN;
		}
		break;
	default:
		OUT = THREE_POSITION_SWITCH_v1::Off;
		IN  = THREE_POSITION_SWITCH_v1::Off;
		break;
	}
}


void THREE_POSITION_2TOF::operator ()(void)
{

	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	ET = tx - StartTime;
	ESP_LOGV(TAG, "ET %i    PT_up %i, PT_down %i", ET, PT_up, PT_down);

	switch (IN){
	case THREE_POSITION_SWITCH_v1::Off:
		switch (OUT) {
		case THREE_POSITION_SWITCH_v1::Momentary_forward_up_right:
		case THREE_POSITION_SWITCH_v1::held_forward_up_right:
			if (ET >= PT_up)
			{
				OUT = THREE_POSITION_SWITCH_v1::Off;
			}
			break;
		case THREE_POSITION_SWITCH_v1::Momentary_backward_down_left:
		case THREE_POSITION_SWITCH_v1::held_backward_down_left:
			if (ET >= PT_down)
			{
				OUT = THREE_POSITION_SWITCH_v1::Off;
			}
			break;
		default:
			OUT = THREE_POSITION_SWITCH_v1::Off;
		}
		break;
	case THREE_POSITION_SWITCH_v1::Momentary_forward_up_right:
	case THREE_POSITION_SWITCH_v1::Momentary_backward_down_left:
		if (OUT != THREE_POSITION_SWITCH_v1::Off)
		{
			ESP_LOGD(TAG, "TOF_1: cancel detected");
			OUT = THREE_POSITION_SWITCH_v1::Off;
			IN  = THREE_POSITION_SWITCH_v1::Off;
		}
		else
		{
			ESP_LOGD(TAG, "TOF_1: raising Edge detected");
			//Start the Timer
			StartTime = tx;
			OUT = IN;
		}
		break;
	case THREE_POSITION_SWITCH_v1::held_forward_up_right:
		if (OUT == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right)
		{
			ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
			OUT = IN;
		}
		break;
	case THREE_POSITION_SWITCH_v1::held_backward_down_left:
		if (OUT == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left)
		{
			ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
			OUT = IN;
		}
		break;
	default:
		OUT = THREE_POSITION_SWITCH_v1::Off;
		IN  = THREE_POSITION_SWITCH_v1::Off;
		break;
	}
}


