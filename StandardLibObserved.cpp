/*
 * StandardLibObserved.cpp
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */




#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "TimerSettings.h"
#include "StandardLibObserved.h"



#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"

static const char * const TAG = "StandardLibObserved";

TOF_R_TRIG_O::TOF_R_TRIG_O(TimerSettings* s, const char* key) {
    _subject = s;
    _key = key;
    _subject->attach(this);
}

TOF_R_TRIG_O::~TOF_R_TRIG_O() {
    _subject->detach(this);
}

void TOF_R_TRIG_O::update(Subject* theChangedSubject) {
    if (theChangedSubject == _subject) {
    	PT = _subject->getPT(_key);
    }
}

bool TOF_R_TRIG_O::operator ()(bool IN)
{
	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();

	// raising Edge
	if (IN && !M)
	{
		ESP_LOGD(TAG, "TOF_1: raising Edge detected");
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
