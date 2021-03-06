/*
 * ExtraLib.h
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef MAIN_EXTRALIB_H_
#define MAIN_EXTRALIB_H_

/**
 *
this is a divider
 */

class DIVIDE
{
public:
    //VAR_OUTPUT
    bool Q0 = false;        /* divider output */
    bool Q1 = false;        /* divider output */
    bool Q2 = false;        /* divider output */
    bool Q3 = false;        /* divider output */
    bool Q4 = false;        /* divider output */
    bool Q5 = false;        /* divider output */
    bool Q6 = false;        /* divider output */
    bool Q7 = false;        /* divider output */
    //call
    bool operator()(int32_t IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */

};



class CYCLE_4_TAP
{
public:
    //VAR_INPUT
    int32_t T0 = 500;
    int32_t T1 = 500;
    int32_t T2 = 500;
    int32_t T3 = 500;
    //VAR_OUTPUT
    int32_t STATE = 0;
    bool Q0 = false;        /* divider output */
    bool Q1 = false;        /* divider output */
    bool Q2 = false;        /* divider output */
    bool Q3 = false;        /* divider output */
    //call
    bool operator()(bool IN);
private:
    bool INIT = false;
    int32_t TX = 0;
    int32_t LAST = 0;
};


class CYCLE_8_TAP
{
public:
    //VAR_INPUT
    int32_t T0 = 500;
    int32_t T1 = 500;
    int32_t T2 = 500;
    int32_t T3 = 500;
    int32_t T4 = 500;
    int32_t T5 = 500;
    int32_t T6 = 500;
    int32_t T7 = 500;
    //VAR_OUTPUT
    int32_t STATE = 0;
    bool Q0 = false;        /* divider output */
    bool Q1 = false;        /* divider output */
    bool Q2 = false;        /* divider output */
    bool Q3 = false;        /* divider output */
    bool Q4 = false;        /* divider output */
    bool Q5 = false;        /* divider output */
    bool Q6 = false;        /* divider output */
    bool Q7 = false;        /* divider output */
    //call
    bool operator()(bool IN);
private:
    bool INIT = false;
    int32_t TX = 0;
    int32_t LAST = 0;
};


#endif /* MAIN_EXTRALIB_H_ */
