/*
 * ExtraLib.h
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef MAIN_EXTRALIB_H_
#define MAIN_EXTRALIB_H_

/**
 *
this is a divider
 */

class DIVIDE
{
public:
	//VAR_OUTPUT
	bool Q0 = false;		/* divider output */
	bool Q1 = false;		/* divider output */
	bool Q2 = false;		/* divider output */
	bool Q3 = false;		/* divider output */
	bool Q4 = false;		/* divider output */
	bool Q5 = false;		/* divider output */
	bool Q6 = false;		/* divider output */
	bool Q7 = false;		/* divider output */
	//call
	bool operator()(int32_t IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */

};


#endif /* MAIN_EXTRALIB_H_ */
