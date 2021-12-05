/*
 * Automation.h
 *
 *  Created on: 18.11.2021
 *      Author: Franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATION_H_
#define COMPONENTS_PLCLIB_AUTOMATION_H_

/**
 * \brief

    INTERLOCK has two inputs I1 and I2 which drive the corresponding outputs Q1 and Q2.
    the inputs signals lock each other out and therfore I1 can only drive Q1 when I2 is Low and vice versa.
    The input TL specifies a dead time between two outputs can become active.
    an output can only become active when the other output was not active for the time TL.

 *
 */
class INTERLOCK
{
    public:
    //VAR_INPUT
    bool I1 = false;        /* input 1 */
    bool I2 = false;        /* input 2 */
    int32_t TL = 10;        /* TIME */            /* lock time */
    //VAR_OUTPUT
    bool Q1 = false;        /* output 1 */
    bool Q2 = false;        /* output 2 */
    //call
    void operator()(void);  /*  */
private:
    TOF T1;
    TOF T2;
};





#endif /* COMPONENTS_PLCLIB_AUTOMATION_H_ */
