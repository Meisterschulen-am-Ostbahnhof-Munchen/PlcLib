/*
 * Automation_FOUR_POSITION.h
 *
 *  Created on: 18.11.2021
 *      Author: Franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATION_FOUR_POSITION_H_
#define COMPONENTS_PLCLIB_AUTOMATION_FOUR_POSITION_H_








enum class FOUR_POSITION_SWITCH_v1 { //Value 1
    Off                          = 0,
    Momentary_forward_up_right   = 1,
    held_forward_up_right        = 2,
    Momentary_backward_down_left = 4,
    held_backward_down_left      = 8,
    Momentary_float              = 16,
    held_float                   = 32
};

/**
 * \brief

    Three-Position    Switch,        (returning    to    centre    position)
    (Momentary    Single    Pole,    Three    Position,    Centre    Off)
    Value    1:
    0    =    Off
    1    =    Momentary    =    forward,    up    or    right
    2    =    held    forward,    up,    or    right
    4    =    Momentary    =    backward,    down    or    left
    8    =    held    backward,    down,    or    left
    Value    2:
    Number    of    transitions    from    Off    to    not    Off    since    power
    up    (Momentary    to    held    is    not    counted).    Overflows
    from    FFFF(16)    to    0.

 *
 */
class FOUR_POSITION_SWITCH
{
    public:
    //VAR_INPUT
    bool I1 = false;        /* input 1 forward,       up or right */
    bool I2 = false;        /* input 2 backward, down or left  */
    bool I3 = false;        /* input 3 float  */
    //VAR_OUTPUT
    FOUR_POSITION_SWITCH_v1 State
        = FOUR_POSITION_SWITCH_v1::Off;        /* output 1 */
    uint16_t Value2 = 0;                        /* output 2 */
    //call
    void operator()(void);  /*  */
};



class VALVE_WITH_FLOAT
{
    public:
    //VAR_INPUT
    FOUR_POSITION_SWITCH_v1 State
        = FOUR_POSITION_SWITCH_v1::Off;        /* Input 1 */
    //VAR_OUTPUT
    bool Q1 = false;        /* output 1                        forward,  up   or right */
    bool Q2 = false;        /* output 2                        backward, down or left  */
    bool Q3 = false;        /* output 3 float and safety Valve forward,  up   or right */
    bool Q4 = false;        /* output 4 float and safety Valve backward, down or left  */
    //call
    void operator()(void);  /*  */
};



#endif /* COMPONENTS_PLCLIB_AUTOMATION_FOUR_POSITION._H_ */
