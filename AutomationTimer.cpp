/*
 * AutomationTimer.cpp
 *
 *  Created on: 22.11.2021
 *      Author: franz
 */



#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"
#include "Automation.h"
#include "AutomationTimer.h"

void THREE_POSITION_TOF::operator ()(void)
{

	int32_t tx;					/* internal variable */

	/* read system timer */
	tx = T_PLC_MS();






	M = IN; //remember old State.



	OUT = IN;

}
