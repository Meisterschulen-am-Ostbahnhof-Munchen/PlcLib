/*
 * StandardLib.h
 *
 *  Created on: 24.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef MAIN_STANDARDLIB_H_
#define MAIN_STANDARDLIB_H_




/**
 * Falling Edge detection.
 */
class F_TRIG
{
public:
	//VAR_OUTPUT
	bool Q = false;					/* Edge detected */
	//call
	bool operator()(bool CLK); /* is TRUE if falling Edge detection. */
private:
	bool M = false;			/* internal variable */
};

/**
 * Rising Edge detection.
 */
class R_TRIG
{
public:
	//VAR_OUTPUT
	bool Q = false;					/* Edge detected */
	//call
	bool operator()(bool CLK); /* is TRUE if rising Edge detection. */
private:
	bool M = false;			/* internal variable */
};






/**
 * \brief
	Counter Up.
	CV is incremented by 1 if CU has a rising edge.
	Q is TRUE, if CV is reached PV.
 *
 */

class CTU
{
public:
	//VAR_INPUT
	bool RESET = false;			/* Reset Counter to 0 */
	int32_t PV;					/* Counter Limit */
	//VAR_OUTPUT
	bool Q = false;				/* Counter reached the Limit */
	int32_t CV = 0; 			/* Current Counter Value */
	//call
	bool operator()(bool CU);/* Count Up */
private:
	bool M = false;			/* Variable for CU Edge Detection */
};






/**
 * \brief
	Bistable function, set dominant
	Q1 = SET1 OR (NOT RESET AND Q1)
 *
 */

class SR
{
public:
	//VAR_OUTPUT
	bool Q1 = false;				/* */
	//call
	bool operator()(bool SET1, bool RESET);/* Count Up */
};



/**
 * \brief
	Bistable function, reset dominant
	Q1 =  NOT RESET1 AND (SET OR Q1)
 *
 */

class RS
{
public:
	//VAR_OUTPUT
	bool Q1 = false;				/**/
	//call
	bool operator()(bool SET, bool RESET1);/* Count Up */
};





/**
 * \brief
	Timer on delay.
	Q is TRUE, PT milliseconds after IN had a rising edge.
 *
 * \param	IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return	Q is TRUE, PT milliseconds after IN had a rising edge.
 *
 */
class TON
{
public:
	//VAR_INPUT
	int32_t PT = 0;
	//VAR_OUTPUT
	bool Q = false;					/* is TRUE, PT milliseconds after IN had a rising edge */
	int32_t ET = 0; 		/* elapsed time */
	//call
	bool operator()(bool IN);/* is TRUE, PT milliseconds after IN had a rising edge */
private:
	bool M = false;			/* internal variable */
	int32_t StartTime = 0;	/* internal variable */
};

/**
 * \brief
	Timer of delay.
	Q is FALSE, PT milliseconds after IN had a falling edge.
 *
 * \param	IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return	Q is FALSE, PT seconds after IN had a falling edge
 *
 */
class TOF
{
public:
	//VAR_INPUT
	int32_t PT = 0;
	//VAR_OUTPUT
	bool Q = false;					/* Q is FALSE, PT milliseconds after IN had a falling edge */
	int32_t ET = 0; 		/* elapsed time */
	//call
	bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
	bool M = false;			/* internal variable */
	int32_t StartTime = 0;	/* internal variable */
};


/**
 * \brief
	Timer of delay.
	Q is FALSE, PT milliseconds after IN had a falling edge.


TOF_1 will extend a pulse on input in for PT seconds.
in addition the timer can be cleared asynchronously with rst.
TOF_1 is the same function as TOF from the standard LIB except the asynchronous reset input.

 *
 * \param	IN starts timer with rising edge, resets timer with falling edge
 * \param   PT time to pass, before Q is set
 * \return	Q is FALSE, PT seconds after IN had a falling edge
 *
 */
class TOF_1
{
public:
	//VAR_INPUT
	int32_t PT = 0;
	bool RST = false;
	//VAR_OUTPUT
	bool Q = false;					/* Q is FALSE, PT milliseconds after IN had a falling edge */
	int32_t ET = 0; 		/* elapsed time */
	//call
	bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
	bool M = false;			/* internal variable */
	int32_t StartTime = 0;	/* internal variable */
};



/**
 * \brief
	Timer Pulse.
	Q produces a High-Signal with the length of PT on every rising edge on IN.
 *
 * \param	IN Trigger for Start of the Signal
 * \param   PT The length of the High-Signal in ms
 * \return	Q is The pulse
 *
 */
class TP
{
public:
	//VAR_INPUT
	int32_t PT = 0;			/* The length of the High-Signal in ms */
	//VAR_OUTPUT
	bool Q = false;					/* The pulse */
	int32_t ET = 0; 		/* The current phase of the High-Signal  */
	//call
	bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
	bool M = false;			/* internal variable */
	int32_t StartTime = 0;	/* internal variable */
};

#endif /* MAIN_STANDARDLIB_H_ */
