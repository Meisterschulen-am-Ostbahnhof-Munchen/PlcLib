/*
 * AutomationTimer_FOUR_POSITION_TOFObserved.h
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATIONTIMER_FOUR_POSITION_TOFOBSERVED_H_
#define COMPONENTS_PLCLIB_AUTOMATIONTIMER_FOUR_POSITION_TOFOBSERVED_H_


#include "Observer.h"

class TimerSettings;
class Subject;




class FOUR_POSITION_TOF_O  : public Observer
{
    public:
	FOUR_POSITION_TOF_O(TimerSettings*, const char * const key);
	FOUR_POSITION_TOF_O(const FOUR_POSITION_TOF_O& a) = delete;
	FOUR_POSITION_TOF_O& operator=(const FOUR_POSITION_TOF_O& other) = delete;
    virtual ~FOUR_POSITION_TOF_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    FOUR_POSITION_SWITCH_v1 IN        = FOUR_POSITION_SWITCH_v1::Off;        /* input 1 */
    //VAR_OUTPUT
    FOUR_POSITION_SWITCH_v1 OUT        = FOUR_POSITION_SWITCH_v1::Off;        /* output 1 */
    int32_t ET = 0;         /* elapsed time */
    //call
    void operator()(void);  /*  */
    private:
    int32_t PT = 0;
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};


#endif /* COMPONENTS_PLCLIB_AUTOMATIONTIMER_FOUR_POSITION_TOFOBSERVED_H_ */
