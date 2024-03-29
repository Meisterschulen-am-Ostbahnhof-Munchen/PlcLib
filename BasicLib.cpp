/*
 * BasicLib.cpp
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */



#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "Operators.h"
#include "TimeLib.h"
#include "StandardLib.h"
#include "BasicLib.h"


#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"

static const char * const TAG = "BasicLib";

bool CLICK_DEC::operator ()(bool IN)
{
    /* Q shall only be active for one cycle only */
    if (IN == false)
    {
        Q0 = false;
        Q1 = false;
        Q2 = false;
        Q3 = false;
    }

    if (IN and not EDGE and not TX.Q)
    {
        /* a rising edge on in sets the counter to 0 */
        CNT = 0;
    }
    else if (TX.Q and not IN and EDGE)
    {
        /* count falling edges when tp.q is true */
        CNT++;
    }
    else if (not TX.Q)
    {
        switch (CNT) {
        case 0 : Q0 = true; break;
        case 1 : Q1 = true; break;
        case 2 : Q2 = true; break;
        case 3 : Q3 = true; break;
        default:            break;
        }
        CNT = -1;
    }

    /* remember the status of IN */
    EDGE = IN;
    TX.PT = TC;
    TX(IN); //Call TX
    return (Q1);
}

bool CLK_DIV::operator ()(bool CLK) {
    if(RST)
    {
        CNT = false;
        Q0  = false;
        Q1  = false;
        Q2  = false;
        Q3  = false;
        Q4  = false;
        Q5  = false;
        Q6  = false;
        Q7  = false;
    }
    else if(CLK)
    {
        CNT = CNT    +1;
        Q0  = CNT &   1;
        Q1  = CNT &   2;
        Q2  = CNT &   4;
        Q3  = CNT &   8;
        Q4  = CNT &  16;
        Q5  = CNT &  32;
        Q6  = CNT &  64;
        Q7  = CNT & 128;
    }
    return (Q0);
}

bool CLK_N::operator ()(void) {
    STIME = T_PLC_MS() >> N;
    CLK = STIME & 1;
    Q = CLK not_eq EDGE;
    EDGE = CLK;
    return (Q);
}

bool CLK_PRG::operator ()(void) {
    /* read system time */
    TX = T_PLC_MS();

    /* INITialize on startup */
    if (not INIT)
    {
        INIT = true;
        LAST = TX - PT;
    }

    /* generate output pulse when next_pulse is reached */
    Q = TX - LAST >= PT;
    if (Q) LAST = TX;
    return (Q);
}

bool CLK_PULSE::operator ()(void) {
    TX = T_PLC_MS();        /* read system */
    Q = false;                /* reset Q we generate pulses only for one cycle */
    RUN = CNT < N;

    if( not INIT or RST)
    {
        ESP_LOGD(TAG, "CLK_PULSE: INIT %" PRIu8 ", RST %" PRIu8 "", INIT, RST);
        INIT = true;
        CNT = 0;
        TN = TX - PT;
        RUN = false;
    }
    else if ((CNT < N or N == 0) and TX - TN >= PT)         /* generate a pulse */
    {
        CNT++;
        Q = true;
        TN += PT;
    }
    ESP_LOGD(TAG, "CLK_PULSE: CNT = %" PRIi32 "", CNT);
    return (Q);
}





int32_t CYCLE_4::operator ()(void)
{
    /* read system timer */
    TX = T_PLC_MS();
    /* INIT on first cycle */
    if (not INIT)
    {
        INIT = true;
        LAST = TX;
    }

    if (E)
    {
        if (SL)
        {
            /* when sx > 0 then the STATE sx is forced to start */
        	const int32_t Min = 0;
        	const int32_t Max = 3;
            STATE= LIMIT(Min, SX, Max);
            LAST = TX;
            /* this is to avoid to reset sx from the calling programm it does work fine on codesys but i am not sure about other systems, because we are writing to an input */
            SL = false;
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
                }
                break;
            case 1 : /* wait for T1 over 1st cycle */
                if( TX - LAST >= T1 )
                {
                        STATE = 2;
                        LAST = TX;
                }
                break;
            case 2 : /* wait for T1 over 1st cycle */
                if( TX - LAST >= T2 )
                {
                        STATE = 3;
                        LAST = TX;
                }
                break;
            case 3 : /* wait for T2 over 2nd cycle */
                if( TX - LAST >= T3 )
                {
                        if (S0) STATE = 0;  /* if S0 is false, the sequence stops at STATE 3 */
                        LAST = TX;
                }
                break;
            default:
                break;
            }
        }
    }
    else
    {
        STATE = 0;
        LAST = TX;
    }

    return (STATE);
}

float FT_PT1::operator ()(float in) {
    /* read system time */
    tx = T_PLC_US();

    /* startup initialisation */
    if (not init or T == 0) {
        init = true;
        out = K * in;
    } else {
        out = out + (in * K - out) * (tx - last) / T * 1.0E-3;
        if (abs(out) < 1.0E-20) out = 0.0;
    }

    last = tx;
    return (out);


    /*
    hm 1.1.2007    rev 1.1
        corrected error while startup value was not correct
        for very small time values real output would run out of range.

    hm 3.1.2007    rev 1.2
        corrected an error for falling edge failures.
        added output faktor K.

    hm 27. 2. 2007    rev 1.3
        output will be input during init for definitive startup condition.

    hm    15.9.2007    rev 1.4
        changed time() to T_PLC_US() for compatibilitxy resons
        increased internal accuracy to Microseconds instead of Milliseconds

    hm    23. oct 2007    rev 1.5
        added out := in to the init statements

    hm    30. nov 2007    rev 1.6
        changed out to be K * in during initialization

    hm    5. jan 2008    rev 1.7
        improved code for better performance

    hm    16. mar. 2008    rev 1.8
        added type conversion to avoid warning under codesys 3.0

    hm    14. jun. 2008    rev 1.9
        improved code

    hm    11. mar. 2009    rev 1.10
        real constants updated to new systax using dot

    hm    18. jan. 2011    rev 1.11
        avoid underrun of out
    */


}

bool TOGGLE::operator ()(bool CLK) {
    /*
	version 1.1	30. oct. 2008
	programmer 	hugo
	tested by	oscat

	toggle flip flop the output changes state with every rising edge of clk.

    */

	if(RST)
		Q = false;
	else if (CLK and not EDGE)
		Q = not Q;
	EDGE = CLK;
	return (Q);

    /* revision history

	hm	13.9.2007		rev 1.0
		original version

	hm	30. oct. 2008	rev 1.1
		deleted unnecessary init

    */

}


