/*
 * StandardLib.c
 *
 *  Created on: 24.08.2021
 *      Author: FranzHoepfinger
 */


#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"



#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"

static const char *TAG = "StandardLib";





bool TON::operator ()(bool IN)
{
	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	// raising Edge
	if (IN && !M)
	{
		ESP_LOGD(TAG, "TON: raising Edge detected");
		//Start the Timer
		StartTime = tx;
	}

	// falling Edge
	if (!IN && M)
	{
		ESP_LOGD(TAG, "TON: falling Edge detected");
		//reset the Timer
		StartTime = 0;
	}


	if (IN)
	{
		ET = tx - StartTime;
	}
	else
	{
		ET = 0;
	}

	M = IN; //remember old State.

	ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);
	Q = ET >= PT ? true : false;
	return (Q);
}

bool F_TRIG::operator ()(bool CLK)
{

	// falling Edge
	if (!CLK && M)
	{
		ESP_LOGD(TAG, "F_TRIG: falling Edge detected");
		Q = 1;
	}
	else
	{
		Q = 0;
	}
	M = CLK; //remember old State.
	return (Q);
}

bool R_TRIG::operator ()(bool CLK)
{

	// rising Edge
	if (CLK && !M)
	{
		ESP_LOGD(TAG, "R_TRIG: rising Edge detected");
		Q = 1;
	}
	else
	{
		Q = 0;
	}
	M = CLK; //remember old State.
	return (Q);
}

bool TOF::operator ()(bool IN)
{
	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	// raising Edge
	if (IN && !M)
	{
		ESP_LOGD(TAG, "TOF: raising Edge detected");
		//reset the Timer
		StartTime = 0;
	}

	// falling Edge
	if (!IN && M)
	{
		ESP_LOGD(TAG, "TOF: falling Edge detected");
		//Start the Timer
		StartTime = tx;
	}


	if (IN)
	{
		Q = true;
		ET = 0;
	}
	else
	{
		ET = tx - StartTime;
	}


	M = IN; //remember old State.

	ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);


	if (ET >= PT)
	{
		Q = false;
	}


	return (Q);
}

bool TOF_1::operator ()(bool IN)
{
	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	// raising Edge
	if (IN && !M)
	{
		ESP_LOGD(TAG, "TOF_1: raising Edge detected");
		//reset the Timer
		StartTime = 0;
	}

	// falling Edge
	if (!IN && M)
	{
		ESP_LOGD(TAG, "TOF_1: falling Edge detected");
		//Start the Timer
		StartTime = tx;
	}


	if (IN)
	{
		Q = true;
		ET = 0;
	}
	else
	{
		ET = tx - StartTime;
	}


	M = IN; //remember old State.

	ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);


	if (ET >= PT)
	{
		Q = false;
	}

	if (RST)
	{
		Q = false;
		RST = false;
	}


	return (Q);
}

bool TP::operator ()(bool IN)
{
	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	// raising Edge
	if (IN && !M && !Q)
	{
		ESP_LOGD(TAG, "TP: raising Edge detected");
		//Start the Timer
		StartTime = tx;
		Q = true;
	}



	if (Q)
	{
		ET = tx - StartTime;
	}
	else
	{
		ET = 0;
		//reset the Timer
		StartTime = 0;
	}


	if (ET >= PT)
	{
		Q = false;
	}

	M = IN; //remember old State.
	return (Q);
}

bool CTU::operator ()(bool CU) {
	if (RESET)
		CV = 0;
	else if (CU && !M)
		CV++;
	M = CU; //remember old State.
	Q = (CV >= PV);
	return (Q);
}

bool SR::operator ()(bool SET1, bool RESET)
{
	Q1 = (!RESET && Q1) || SET1;
	return (Q1);
}

bool RS::operator ()(bool SET, bool RESET1)
{
	Q1 = !RESET1 && (Q1 || SET);
	return (Q1);
}
