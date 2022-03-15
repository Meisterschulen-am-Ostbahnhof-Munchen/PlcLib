/*
 * ExtraLib.cpp
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */


#include <stdbool.h>
#include <stdint.h>
#include "Operators.h"
#include "TimeLib.h"
#include "StandardLib.h"
#include "ExtraLib.h"

bool DIVIDE::operator ()(int32_t IN)
{
    Q0  = (IN == 0);
    Q1  = (IN == 1);
    Q2  = (IN == 2);
    Q3  = (IN == 3);
    Q4  = (IN == 4);
    Q5  = (IN == 5);
    Q6  = (IN == 6);
    Q7  = (IN == 7);
    return (Q0);
}

bool CYCLE_4_TAP::operator ()(bool IN) {
    Q0  = false;
    Q1  = false;
    Q2  = false;
    Q3  = false;
    /* read system timer */
    TX = T_PLC_MS();
    /* INIT on first cycle */
    if (not INIT)
    {
        INIT = true;
        LAST = TX;
    }

    if (IN)
    {
        STATE= 0;
        LAST = TX;
    }
    else
    {
        switch(STATE)
        {
        case 0 :    /* wait for T0 and switch to next cycle */
            if( TX - LAST >= T0 )
            {
                    STATE = 1;
                    LAST = TX;
                    Q0 = true;
            }
            break;
        case 1 : /* wait for T1 over 1st cycle */
            if( TX - LAST >= T1 )
            {
                    STATE = 2;
                    LAST = TX;
                    Q1 = true;
            }
            break;
        case 2 : /* wait for T2 over 2nd cycle */
            if( TX - LAST >= T2 )
            {
                    STATE = 3;
                    LAST = TX;
                    Q2 = true;
            }
            break;
        case 3 : /* wait for T3 over 3rd cycle */
            if( TX - LAST >= T3 )
            {
                    LAST = TX;
                    Q3 = true;
            }
            break;
        default:
            break;
        }
    }

    return (Q0);
}


bool CYCLE_8_TAP::operator ()(bool IN) {
    Q0  = false;
    Q1  = false;
    Q2  = false;
    Q3  = false;
    Q4  = false;
    Q5  = false;
    Q6  = false;
    Q7  = false;
    /* read system timer */
    TX = T_PLC_MS();
    /* INIT on first cycle */
    if (not INIT)
    {
        INIT = true;
        LAST = TX;
    }

    if (IN)
    {
        STATE= 0;
        LAST = TX;
    }
    else
    {
        switch(STATE)
        {
        case 0 :    /* wait for T0 and switch to next cycle */
            if( TX - LAST >= T0 )
            {
                    STATE = 1;
                    LAST = TX;
                    Q0 = true;
            }
            break;
        case 1 : /* wait for T1 over 1st cycle */
            if( TX - LAST >= T1 )
            {
                    STATE = 2;
                    LAST = TX;
                    Q1 = true;
            }
            break;
        case 2 : /* wait for T2 over 2nd cycle */
            if( TX - LAST >= T2 )
            {
                    STATE = 3;
                    LAST = TX;
                    Q2 = true;
            }
            break;
        case 3 : /* wait for T3 over 3rd cycle */
            if( TX - LAST >= T3 )
            {
                    LAST = TX;
                    Q3 = true;
            }
        case 4 : /* wait for T4 over 4th cycle */
            if( TX - LAST >= T4 )
            {
                    LAST = TX;
                    Q4 = true;
            }
        case 5 : /* wait for T5 over 5th cycle */
            if( TX - LAST >= T5 )
            {
                    LAST = TX;
                    Q5 = true;
            }
        case 6 : /* wait for T6 over 6th cycle */
            if( TX - LAST >= T6 )
            {
                    LAST = TX;
                    Q6 = true;
            }
        case 7 : /* wait for T7 over 7th cycle */
            if( TX - LAST >= T7 )
            {
                    LAST = TX;
                    Q7 = true;
            }
            break;
        default:
            break;
        }
    }

    return (Q0);
}



