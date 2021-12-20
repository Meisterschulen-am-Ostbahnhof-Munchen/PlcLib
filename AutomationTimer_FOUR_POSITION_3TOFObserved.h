/*
 * AutomationTimer_FOUR_POSITION_3TOFObserved.h
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATIONTIMER_FOUR_POSITION_3TOFOBSERVED_H_
#define COMPONENTS_PLCLIB_AUTOMATIONTIMER_FOUR_POSITION_3TOFOBSERVED_H_


#include "Observer.h"


class TimerSettings3;
class Subject;


class FOUR_POSITION_3TOF_O  : public Observer
{
    public:
	FOUR_POSITION_3TOF_O(TimerSettings3*, const char * const key_up, const char * const key_down, const char * const key_float);
	FOUR_POSITION_3TOF_O(const FOUR_POSITION_3TOF_O& a) = delete;
	FOUR_POSITION_3TOF_O& operator=(const FOUR_POSITION_3TOF_O& other) = delete;
    virtual ~FOUR_POSITION_3TOF_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    FOUR_POSITION_SWITCH_v1 IN        = FOUR_POSITION_SWITCH_v1::Off;        /* input 1 */
    //VAR_OUTPUT
    FOUR_POSITION_SWITCH_v1 OUT        = FOUR_POSITION_SWITCH_v1::Off;        /* output 1 */
    int32_t ET = 0;         /* elapsed time */
    //call
    void operator()(void);  /*  */
    private:
    int32_t PT_up   = 0;
    int32_t PT_down = 0;
    int32_t PT_float = 0;
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings3* _subject;
    const char * const _key_up;
    const char * const _key_down;
    const char * const _key_float;
};



#endif /* COMPONENTS_PLCLIB_AUTOMATIONTIMER_FOUR_POSITION_3TOFOBSERVED_H_ */
