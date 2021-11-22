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


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

static const char *TAG = "AutomationTimer";

void THREE_POSITION_TOF::operator ()(void)
{

	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();


	if (
		M == THREE_POSITION_SWITCH_v1::Off
		&&
		OUT == THREE_POSITION_SWITCH_v1::Off
		&&
		IN == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left
	   )
	{
		ESP_LOGD(TAG, "TOF_1: raising Edge detected");
		//Start the Timer
		StartTime = tx;
		M   = IN;
		OUT = IN;
	}

	if (
		M == THREE_POSITION_SWITCH_v1::Off
		&&
		OUT == THREE_POSITION_SWITCH_v1::Off
		&&
		IN == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right
	   )
	{
		ESP_LOGD(TAG, "TOF_1: raising Edge detected");
		//Start the Timer
		StartTime = tx;
		M   = IN;
		OUT = IN;
	}

	if (
		M == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left
		&&
		OUT == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left
		&&
		IN == THREE_POSITION_SWITCH_v1::held_backward_down_left
	   )
	{
		ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
		M   = IN;
		OUT = IN;
	}

	if (
		M == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right
		&&
		OUT == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right
		&&
		IN == THREE_POSITION_SWITCH_v1::held_forward_up_right
	   )
	{
		ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
		M   = IN;
		OUT = IN;
	}



	if (
		M == THREE_POSITION_SWITCH_v1::Off
		&&
		OUT != THREE_POSITION_SWITCH_v1::Off
		&&
		IN == THREE_POSITION_SWITCH_v1::Momentary_forward_up_right
	   )
	{
		ESP_LOGD(TAG, "TOF_1: cancel detected");
		M = THREE_POSITION_SWITCH_v1::Off;
		OUT = THREE_POSITION_SWITCH_v1::Off;
		IN = THREE_POSITION_SWITCH_v1::Off;
	}
	if (
		M == THREE_POSITION_SWITCH_v1::Off
		&&
		OUT != THREE_POSITION_SWITCH_v1::Off
		&&
		IN == THREE_POSITION_SWITCH_v1::Momentary_backward_down_left
	   )
	{
		ESP_LOGD(TAG, "TOF_1: cancel detected");
		M = THREE_POSITION_SWITCH_v1::Off;
		OUT = THREE_POSITION_SWITCH_v1::Off;
		IN = THREE_POSITION_SWITCH_v1::Off;
	}


	if (
		M != THREE_POSITION_SWITCH_v1::Off
		&&
		OUT != THREE_POSITION_SWITCH_v1::Off
		&&
		IN != THREE_POSITION_SWITCH_v1::Off
	   )
	{
		ET = 0;
	}
	else
	{
		ET = tx - StartTime;
	}




	M = IN; //remember old State.

	ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);


	if (IN == THREE_POSITION_SWITCH_v1::Off) //This FB is INPUT First Priority.
	{
		if (ET >= PT)
		{
			OUT = THREE_POSITION_SWITCH_v1::Off;
		}
	}







}
