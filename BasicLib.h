/*
 * BasicLib.h
 *
 *  Created on: 25.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef MAIN_BASICLIB_H_
#define MAIN_BASICLIB_H_


/**
 * \brief

	this Module detects a rising edge on In and decodes the amount of falling edges (Pulses) within a specified time TC.
	the outputs Q0..Q3 will go true for one cycle and the amount of clicks within a specified time TC.
	if only a rising egde is detected within TC Q0 will respond, Q1 for 1 pulse and so on..
 *

 *
 */
class CLICK_DEC
{
public:
	//VAR_INPUT
	int32_t TC = 0;			/* TIME */
	//VAR_OUTPUT
	bool Q0 = false;		/* output signal rising edge without falling edge */
	bool Q1 = false;		/* output signal of a pulse within TC */
	bool Q2 = false;		/* output signal of a pulse within TC */
	bool Q3 = false;		/* output signal of a pulse within TC */
	//call
	bool operator()(bool IN);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
	TP TX;					/* internal variable */
	bool EDGE = false;			/* internal variable */
	int32_t CNT = -1;			/* TIME */
};


/**
 *
this is a clock divider
each output divides the signal by 2
Q0 = clk / 2 , Q1 = Q0 / 2 and so on.
the outputs have a 50% duty cycle each.
 */

class CLK_DIV
{
public:
	//VAR_INPUT
	bool RST = false;		/* Reset input */
	//VAR_OUTPUT
	bool Q0 = false;		/* divider output CLK / 2 */
	bool Q1 = false;		/* divider output CLK / 4 */
	bool Q2 = false;		/* divider output CLK / 8) */
	bool Q3 = false;		/* divider output CLK / 16) */
	bool Q4 = false;		/* divider output CLK / 32) */
	bool Q5 = false;		/* divider output CLK / 64) */
	bool Q6 = false;		/* divider output CLK / 128) */
	bool Q7 = false;		/* divider output CLK / 256) */
	//call
	bool operator()(bool CLK);/* Q is FALSE, PT milliseconds after IN had a falling edge */
private:
	uint8_t CNT = 0;			/* counter */
};




/**
 *
clk_N uses the internal sps time to generate one pulse every N ms
every pulse is only valid for one cycle so that a edge trigger is not necessary
clk_N generates pulses depending on the accuracy of the system clock.
The input N controlls the period time of the clock.
N=0 equals 1ms, N=1 equals 2ms, N=2 equals 4ms, N=3 equals 8ms ....

be careful, 1ms clocks will only work on very powerful sps cpu's
 *
 */
class CLK_N
{
public:
	//VAR_INPUT
	int32_t N = 0;			/* N=0 equals 1ms, N=1 equals 2ms, N=2 equals 4ms, N=3 equals 8ms .... */
	//VAR_OUTPUT
	bool Q = false;			/* divider output CLK / 2 */
	//call
	bool operator()(void);
private:
	bool EDGE = 0;
	int32_t STIME = 0;
	bool CLK = 0;
};


/**
 *


clk_prg uses the internal sps time to generate a clock with programmable period time.
the first cycle after start is a clk pulse and then depending on the programmed period time a delay.
every pulse is only valid for one cycle.
the accuracy of clk_prg is depending on the accuracy of the system clock.
 *
 */
class CLK_PRG
{
public:
	//VAR_INPUT
	int32_t PT = 10;			/* TIME */
	//VAR_OUTPUT
	bool Q = false;			    /* Tick */
	//call
	bool operator()(void);
private:
	bool INIT = false;;
	int32_t LAST = 0;
	int32_t TX = 0;
};



/**
 *
 *
clk_pulse uses the internal sps time to generate a clock with programmable period time.
the period time is defined for 10ms .. 65s.
pulse generation is continuous if N = 0 and for n pulses otherwise.
the first cycle after start is a clk pulse and then depending on the programmed period time a delay.
every pulse is only valid for one cycle so that a edge trigger is not necessary
clk_prg depending on the accuracy of the system clock.
 *
 *
 */
class CLK_PULSE
{
public:
	//VAR_INPUT
	int32_t PT = 10;			/* TIME */
	int32_t N = 0;
	bool RST = false;
	//VAR_OUTPUT
	bool Q = false;			    /* Tick */
	int32_t CNT = 0;
	bool RUN = false;
	//call
	bool operator()(void);
private:
	bool INIT = false;
	int32_t TX = 0;
	int32_t TN = 0;
};





class CYCLE_4
{
public:
	//VAR_INPUT
	bool E = true;
	int32_t T0 = 500;
	int32_t T1 = 1000;
	int32_t T2 = 1500;
	int32_t T3 = 2000;
	bool S0 = false;
	int32_t SX = 0;
	bool SL = false;
	//VAR_OUTPUT
	int32_t STATE = 0;
	//call
	int32_t operator()(void);
private:
	bool INIT = false;
	int32_t TX = 0;
	int32_t LAST = 0;
};








#endif /* MAIN_BASICLIB_H_ */
