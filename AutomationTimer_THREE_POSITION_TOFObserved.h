/*
 * AutomationTimer_THREE_POSITION_TOFObserved.h
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATIONTIMER_THREE_POSITION_TOFOBSERVED_H_
#define COMPONENTS_PLCLIB_AUTOMATIONTIMER_THREE_POSITION_TOFOBSERVED_H_





class THREE_POSITION_TOF_O
{
    public:
	THREE_POSITION_TOF_O(TimerSettings*, const char * const key);
	THREE_POSITION_TOF_O(const THREE_POSITION_TOF_O& a) = delete;
	THREE_POSITION_TOF_O& operator=(const THREE_POSITION_TOF_O& other) = delete;
    virtual ~THREE_POSITION_TOF_O();

    virtual void update(Subject*);   // overrides Observer operation
    //VAR_INPUT

    THREE_POSITION_SWITCH_v1 IN        = THREE_POSITION_SWITCH_v1::Off;        /* input 1 */
    //VAR_OUTPUT
    THREE_POSITION_SWITCH_v1 OUT    = THREE_POSITION_SWITCH_v1::Off;        /* output 1 */
    int32_t ET = 0;         /* elapsed time */
    //call
    void operator()(void);  /*  */
    private:
    int32_t PT = 0;
    int32_t StartTime = 0;  /* internal variable */
    TimerSettings* _subject;
    const char * const _key;
};



#endif /* COMPONENTS_PLCLIB_AUTOMATIONTIMER_THREE_POSITION_TOFOBSERVED_H_ */
