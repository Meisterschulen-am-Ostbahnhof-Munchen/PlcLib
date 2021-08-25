/*
 * ExtraLib.cpp
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */


#include <stdbool.h>
#include <stdint.h>
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
