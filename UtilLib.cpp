/*
 * UtilLib.cpp
 *
 *  Created on: 24.08.2021
 *      Author: FranzHoepfinger
 */



#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"
#include "UtilLib.h"






bool BLINK::operator ()(bool ENABLE) {
	CLOCK(true);					/* call Timer */
	if (CLOCK.Q==false && ENABLE) 	/* time passed or init */
	{
		CLOCK(false);				/* reset Timer */
		CLOCK(true);				/* restart Timer */
		if (OUT==false)
		{
			CLOCK.PT = TIMEHIGH;
		}
		else
		{
			CLOCK.PT = TIMELOW;
		}
		OUT = ! OUT;				/* invert */
	}
	return (OUT);
}
