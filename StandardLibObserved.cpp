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





bool TON_O::operator ()(bool IN)
{
    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    // raising Edge
    if (IN and not M)
    {
        ESP_LOGD(TAG, "TON: raising Edge detected");
        //Start the Timer
        StartTime = tx;
    }

    // falling Edge
    if (not IN and M)
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
bool TOF_O::operator ()(bool IN)
{
    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    // raising Edge
    if (IN and not M)
    {
        ESP_LOGD(TAG, "TOF: raising Edge detected");
        //reset the Timer
        StartTime = 0;
    }

    // falling Edge
    if (not IN and M)
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

bool TOF_1_O::operator ()(bool IN)
{
    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    // raising Edge
    if (IN and not M)
    {
        ESP_LOGD(TAG, "TOF_1: raising Edge detected");
        //reset the Timer
        StartTime = 0;
    }

    // falling Edge
    if (not IN and M)
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

bool TP_O::operator ()(bool IN)
{
    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    // raising Edge
    if (IN and not M and not Q)
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


TOF_R_TRIG_O::TOF_R_TRIG_O(TimerSettings* s, const char * const key)
	: _subject(s),
	  _key(key)

{
    _subject->attach(this);
}

TOF_R_TRIG_O::~TOF_R_TRIG_O()
{
    _subject->detach(this);
}

void TOF_R_TRIG_O::update(Subject* theChangedSubject)
{
    if (theChangedSubject == _subject) {
        PT = _subject->getPT(_key);
    }
}

bool TOF_R_TRIG_O::operator ()(bool IN)
{
    int32_t tx;                    /* internal variable */

    /* read system timer */
    tx = T_PLC_MS();

    // raising Edge
    if (IN and not M)
    {
        ESP_LOGD(TAG, "TOF_1: raising Edge detected");
        //Start the Timer
        StartTime = tx;
        Q = true;
    }

    ET = tx - StartTime;



    M = IN; //remember old State.

    ESP_LOGV(TAG, "ET %i    PT %i", ET, PT);

    if (not IN) //This FB is INPUT First Priority.
    {
        if (ET >= PT)
        {
            Q = false;
        }


        if (RST)
        {
            Q = false;
            RST = false;
        }
    }

    return (Q);
}
