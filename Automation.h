/*
 * Automation.h
 *
 *  Created on: 18.11.2021
 *      Author: Franz
 */

#ifndef COMPONENTS_PLCLIB_AUTOMATION_H_
#define COMPONENTS_PLCLIB_AUTOMATION_H_

/**
 * \brief

	INTERLOCK has two inputs I1 and I2 which drive the corresponding outputs Q1 and Q2.
	the inputs signals lock each other out and therfore I1 can only drive Q1 when I2 is Low and vice versa.
	The input TL specifies a dead time between two outputs can become active.
	an output can only become active when the other output was not active for the time TL.

 *
 */
class INTERLOCK
{
	public:
	//VAR_INPUT
	bool I1 = false;		/* input 1 */
	bool I2 = false;		/* input 2 */
	int32_t TL = 10;		/* TIME */			/* lock time */
	//VAR_OUTPUT
	bool Q1 = false;		/* output 1 */
	bool Q2 = false;		/* output 2 */
	//call
	void operator()(void);  /*  */
private:
	TOF T1;
	TOF T2;
};




enum THREE_POSITION_SWITCH_v1{
	Off                          = 0,
	Momentary_forward_up_right   = 1,
	held_forward_up_right        = 2,
	Momentary_backward_down_left = 4,
	held_backward_down_left      = 8
};

/**
 * \brief

	Three-Position	Switch,		(returning	to	centre	position)
	(Momentary	Single	Pole,	Three	Position,	Centre	Off)
	Value	1:
	0	=	Off
	1	=	Momentary	=	forward,	up	or	right
	2	=	held	forward,	up,	or	right
	4	=	Momentary	=	backward,	down	or	left
	8	=	held	backward,	down,	or	left
	Value	2:
	Number	of	transitions	from	Off	to	not	Off	since	power
	up	(Momentary	to	held	is	not	counted).	Overflows
	from	FFFF(16)	to	0.

 *
 */
class THREE_POSITION_SWITCH
{
	public:
	//VAR_INPUT
	bool I1 = false;		/* input 1 forward,	up or right */
	bool I2 = false;		/* input 2 backward, down or left */
	//VAR_OUTPUT
	THREE_POSITION_SWITCH_v1 State = Off;		/* output 1 */
	uint16_t Value2 = 0;		/* output 2 */
	//call
	void operator()(void);  /*  */
};










#endif /* COMPONENTS_PLCLIB_AUTOMATION_H_ */
