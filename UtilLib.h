/*
 * UtilLib.h
 *
 *  Created on: 24.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef MAIN_UTILLIB_H_
#define MAIN_UTILLIB_H_


/**
 * Function block to simulate a turn signal
 */
class BLINK
{
public:
	//VAR_INPUT
	int32_t TIMELOW = 0;
	int32_t TIMEHIGH = 0;
	//VAR_OUTPUT
	bool OUT = false;					/* output variable, starting with FALSE  */
	//call
	bool operator()(bool ENABLE); /* TRUE:run Blink, FALSE: OUT keeps its value*/
private:
	TP CLOCK;			/* internal variable */
};


#endif /* MAIN_UTILLIB_H_ */
