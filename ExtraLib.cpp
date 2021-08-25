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
	if (!INIT)
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
		case 0 :	/* wait for T0 and switch to next cycle */
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
		case 2 : /* wait for T1 over 1st cycle */
			if( TX - LAST >= T2 )
			{
					STATE = 3;
					LAST = TX;
					Q2 = true;
			}
			break;
		case 3 : /* wait for T2 over 2nd cycle */
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
