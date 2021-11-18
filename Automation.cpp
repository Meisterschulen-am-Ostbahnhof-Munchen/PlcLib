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

                                         if(!I1 && !I2){        State = Off;        return;      } //Off is Off. nothing else.
    switch (State) {
    case Off:                            if( I1 && !I2){  State = Momentary_forward_up_right;    }			//if we was off, we go mom.
                                         if(!I1 &&  I2){  State = Momentary_backward_down_left;  } break;
    case Momentary_forward_up_right:     if( I1       ){  State = held_forward_up_right;         } break;  //held
    case Momentary_backward_down_left:   if(        I2){  State = held_backward_down_left;       } break;  //held
    default:
    case held_forward_up_right:
    case held_backward_down_left:        /*NOOP*/                                                  break; //nothing to do.
    }

}
