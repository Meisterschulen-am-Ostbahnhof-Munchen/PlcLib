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







void THREE_POSITION_SWITCH::operator ()(void) {

    /* any case */                       if(!I1 && !I2) {        State = Off;        return;      }         //Off is Off. nothing else.
    switch (State) { /* in case */                                                                          //
    case Off:                            if( I1 && !I2) {  State = Momentary_forward_up_right;    }         //if we was off, we go mom.
                                         if(!I1 &&  I2) {  State = Momentary_backward_down_left;  } break;  //if we was off, we go mom.
    case Momentary_forward_up_right:     if( I1       ) {  State = held_forward_up_right;         } break;  // held
    case Momentary_backward_down_left:   if(        I2) {  State = held_backward_down_left;       } break;  // held
    case held_forward_up_right:          if(!I1       ) {  State = Off;                           } break;  // only exit if Button is no more pressed.
    case held_backward_down_left:        if(       !I2) {  State = Off;                           } break;  // only exit if Button is no more pressed.
    default:                                            {  State = Off;                           } break;  // ERROR
    }

}

void THREE_POSITION_VALVE::operator ()(void) {

	switch (State){
	case Off:                             Q1 = false; Q2 = false; break;
	case Momentary_forward_up_right:      Q1 = true;  Q2 = false; break;
	case held_forward_up_right:           Q1 = true;  Q2 = false; break;
	case Momentary_backward_down_left:    Q1 = false; Q2 = true;  break;
	case held_backward_down_left:         Q1 = false; Q2 = true;  break;
	default:                              Q1 = false; Q2 = false; break;
	}


}
