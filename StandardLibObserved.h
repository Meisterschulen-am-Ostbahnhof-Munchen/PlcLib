/*
 * StandardLibObserved.h
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_STANDARDLIBOBSERVED_H_
#define COMPONENTS_PLCLIB_STANDARDLIBOBSERVED_H_


#include "Observer.h"

class TimerSettings;
class Subject;


/**
 * \brief
    Timer of delay.
    Q is FALSE, PT milliseconds after IN had a Rising Edge !!!!!!.


TOF_1 will extend a pulse on input in for PT seconds.
in addition the timer can be cleared asynchronously with rst.
TOF_1 is the same function as TOF from the standard LIB except the asynchronous reset input.

 *
 * \param    IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return    Q is FALSE, PT seconds after IN had a falling edge
 *
 */
class TOF_R_TRIG_O : public Observer
{
public:
    TOF_R_TRIG_O(TimerSettings*, const char* key);
    virtual ~TOF_R_TRIG_O();

    virtual void update(Subject*);
        // overrides Observer operation
    //VAR_INPUT
    bool RST = false;
    //VAR_OUTPUT
    bool Q = false;                    /* Q is FALSE, PT milliseconds after IN had a falling edge */
    int32_t ET = 0;         /* elapsed time */
    //call
    bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
    bool M = false;            /* internal variable */
    int32_t PT = 0;            /* internal variable */
    int32_t StartTime = 0;    /* internal variable */
    TimerSettings* _subject;
    const char* _key;
};


#endif /* COMPONENTS_PLCLIB_STANDARDLIBOBSERVED_H_ */
