/*
 * Automation.cpp
 *
 *  Created on: 18.11.2021
 *      Author: Franz
 */


#include <stdbool.h>
#include <stdint.h>
#include "TimeLib.h"
#include "StandardLib.h"
#include "Automation.h"






void INTERLOCK::operator ()(void) {

	/* the input signal have a run delay to lockout the other input */
	T1.PT = TL;
	T2.PT = TL;
	T1(I1);
	T2(I2);

	Q1 = I1 && !T2.Q;
	Q2 = I2 && !T1.Q;

}
