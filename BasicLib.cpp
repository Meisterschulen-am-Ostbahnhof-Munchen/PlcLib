/*
 * BasicLib.cpp
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */



#include <stdbool.h>
#include <stdint.h>
#include "Operators.h"
#include "TimeLib.h"
#include "StandardLib.h"
#include "BasicLib.h"


#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"

static const char *TAG = "BasicLib";

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

	if (IN && !EDGE && !TX.Q)
	{
		/* a rising edge on in sets the counter to 0 */
		CNT = 0;
	}
	else if (TX.Q && !IN && EDGE)
	{
		/* count falling edges when tp.q is true */
		CNT++;
	}
	else if (!TX.Q)
	{
		switch (CNT) {
		case 0 : Q0 = true; break;
		case 1 : Q1 = true; break;
		case 2 : Q2 = true; break;
		case 3 : Q3 = true; break;
		default:			break;
		}
		CNT = -1;
	};

	/* remember the status of IN */
	EDGE = IN;
	TX.PT = TC;
	TX(IN); //Call TX
	return (Q1);
}

bool CLK_DIV::operator ()(bool CLK) {
	if(RST)
	{
		CNT = 0;
		Q0  = 0;
		Q1  = 0;
		Q2  = 0;
		Q3  = 0;
		Q4  = 0;
		Q5  = 0;
		Q6  = 0;
		Q7  = 0;
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
	Q = CLK ^ EDGE;
	EDGE = CLK;
	return (Q);
}

bool CLK_PRG::operator ()(void) {
	/* read system time */
	TX = T_PLC_MS();

	/* INITialize on startup */
	if (!INIT)
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
	TX = T_PLC_MS();		/* read system */
	Q = false;				/* reset Q we generate pulses only for one cycle */
	RUN = CNT < N;

	if( !INIT || RST)
	{
		ESP_LOGD(TAG, "CLK_PULSE: INIT %i, RST %i", INIT, RST);
		INIT = true;
		CNT = 0;
		TN = TX - PT;
		RUN = false;
	}
	else if ((CNT < N || N == 0) && TX - TN >= PT) 		/* generate a pulse */
	{
		CNT++;
		Q = true;
		TN += PT;
	}
	ESP_LOGD(TAG, "CLK_PULSE: CNT = %i", CNT);
	return (Q);
}





int32_t CYCLE_4::operator ()(void)
{
	/* read system timer */
	TX = T_PLC_MS();
	/* INIT on first cycle */
	if (!INIT)
	{
		INIT = true;
		LAST = TX;
	}

	if (E)
	{
		if (SL)
		{
			/* when sx > 0 then the STATE sx is forced to start */
			STATE= LIMIT(0,SX,3);
			LAST = TX;
			/* this is to avoid to reset sx from the calling programm it does work fine on codesys but i am not sure about other systems, because we are writing to an input */
			SL = false;
		}
		else
		{
			switch(STATE)
			{
			case 0 :	/* wait for T0 and switch to next cycle */
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



