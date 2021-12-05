/*
 * AutomationTimer.h
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATIONTIMER_H_
#define COMPONENTS_PLCLIB_AUTOMATIONTIMER_H_





class THREE_POSITION_TOF
{
    public:
    //VAR_INPUT
    int32_t PT = 0;
    THREE_POSITION_SWITCH_v1 IN        = THREE_POSITION_SWITCH_v1::Off;        /* input 1 */
    //VAR_OUTPUT
    THREE_POSITION_SWITCH_v1 OUT    = THREE_POSITION_SWITCH_v1::Off;        /* output 1 */
    int32_t ET = 0;         /* elapsed time */
    //call
    void operator()(void);  /*  */
    private:
    int32_t StartTime = 0;  /* internal variable */
};





class FOUR_POSITION_TOF
{
    public:
    //VAR_INPUT
    int32_t PT = 0;
    FOUR_POSITION_SWITCH_v1 IN        = FOUR_POSITION_SWITCH_v1::Off;        /* input 1 */
    //VAR_OUTPUT
    FOUR_POSITION_SWITCH_v1 OUT        = FOUR_POSITION_SWITCH_v1::Off;        /* output 1 */
    int32_t ET = 0;         /* elapsed time */
    //call
    void operator()(void);  /*  */
    private:
    int32_t StartTime = 0;    /* internal variable */
};



#endif /* COMPONENTS_PLCLIB_AUTOMATIONTIMER_H_ */
