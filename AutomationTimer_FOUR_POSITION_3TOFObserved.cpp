/*
 * AutomationTimer_FOUR_POSITION_3TOFObserved.cpp
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */




#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "Automation_FOUR_POSITION.h"
#include "TimerSettings3.h"
#include "AutomationTimer_FOUR_POSITION_3TOFObserved.h"


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

static const char * const TAG = "AutomationTimer_FOUR_POSITION_3TOF";


FOUR_POSITION_3TOF_O::FOUR_POSITION_3TOF_O(TimerSettings3* s, const char * const key_up, const char * const key_down, const char * const key_float)
	: _subject(s),
	  _key_up(key_up),
	  _key_down(key_down),
	  _key_float(key_float)	  

{
    _subject->attach(this);
}

FOUR_POSITION_3TOF_O::~FOUR_POSITION_3TOF_O()
{
    _subject->detach(this);
}

void FOUR_POSITION_3TOF_O::update(Subject* theChangedSubject)
{
    if (theChangedSubject == _subject) {
    	PT_up = _subject->getPT_up(_key_up);
		PT_down = _subject->getPT_down(_key_down);
		PT_float = _subject->getPT_float(_key_float);
    }
}

void FOUR_POSITION_3TOF_O::operator ()(void)
{

    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    ET = tx - StartTime;
    ESP_LOGV(TAG, "ET %" PRIi32 "    PT_up %" PRIi32 ", PT_down %" PRIi32 ", PT_float %" PRIi32 "", ET, PT_up, PT_down, PT_float);

    switch (IN){
    case FOUR_POSITION_SWITCH_v1::Off:
        switch (OUT) {
        case FOUR_POSITION_SWITCH_v1::Momentary_forward_up_right:
        case FOUR_POSITION_SWITCH_v1::held_forward_up_right:
            if (ET >= PT_up)
            {
                OUT = FOUR_POSITION_SWITCH_v1::Off;
            }
            break;
        case FOUR_POSITION_SWITCH_v1::Momentary_backward_down_left:
        case FOUR_POSITION_SWITCH_v1::held_backward_down_left:
            if (ET >= PT_down)
            {
                OUT = FOUR_POSITION_SWITCH_v1::Off;
            }
            break;
        case FOUR_POSITION_SWITCH_v1::Momentary_float:
        case FOUR_POSITION_SWITCH_v1::held_float:
            if (ET >= PT_float)
            {
                OUT = FOUR_POSITION_SWITCH_v1::Off;
            }
            break;
        default:
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


