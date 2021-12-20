/*
 * AutomationTimer_FOUR_POSITION_TOFObserved.cpp
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */



#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "Automation_FOUR_POSITION.h"
#include "TimerSettings.h"
#include "AutomationTimer_FOUR_POSITION_TOFObserved.h"


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

static const char * const TAG = "AutomationTimer_FOUR_POSITION_TOF";

FOUR_POSITION_TOF_O::FOUR_POSITION_TOF_O(TimerSettings* s, const char * const key)
	: _subject(s),
	  _key(key)

{
    _subject->attach(this);
}

FOUR_POSITION_TOF_O::~FOUR_POSITION_TOF_O()
{
    _subject->detach(this);
}

void FOUR_POSITION_TOF_O::update(Subject* theChangedSubject)
{
    if (theChangedSubject == _subject) {
        PT = _subject->getPT(_key);
    }
}

void FOUR_POSITION_TOF_O::operator ()(void)
{

    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    ET = tx - StartTime;
    ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);

    switch (IN){
    case FOUR_POSITION_SWITCH_v1::Off:
        if (ET >= PT)
        {
            OUT = FOUR_POSITION_SWITCH_v1::Off;
        }
        break;
    case FOUR_POSITION_SWITCH_v1::Momentary_forward_up_right:
    case FOUR_POSITION_SWITCH_v1::Momentary_backward_down_left:
    case FOUR_POSITION_SWITCH_v1::Momentary_float:
        if (OUT not_eq FOUR_POSITION_SWITCH_v1::Off)
        {
            ESP_LOGD(TAG, "TOF_1: cancel detected");
            OUT = FOUR_POSITION_SWITCH_v1::Off;
            IN  = FOUR_POSITION_SWITCH_v1::Off;
        } else {
            ESP_LOGD(TAG, "TOF_1: raising Edge detected");
            //Start the Timer
            StartTime = tx;
            OUT = IN;
        }
        break;
    case FOUR_POSITION_SWITCH_v1::held_forward_up_right:
        if (OUT == FOUR_POSITION_SWITCH_v1::Momentary_forward_up_right)
        {
            ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
            OUT = IN;
        }
        break;
    case FOUR_POSITION_SWITCH_v1::held_backward_down_left:
        if (OUT == FOUR_POSITION_SWITCH_v1::Momentary_backward_down_left)
        {
            ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
            OUT = IN;
        }
        break;
    case FOUR_POSITION_SWITCH_v1::held_float:
        if (OUT == FOUR_POSITION_SWITCH_v1::Momentary_float)
        {
            ESP_LOGD(TAG, "TOF_1: raising Edge II detected");
            OUT = IN;
        }
        break;
    default:
        OUT = FOUR_POSITION_SWITCH_v1::Off;
        IN  = FOUR_POSITION_SWITCH_v1::Off;
        break;
    }
}


