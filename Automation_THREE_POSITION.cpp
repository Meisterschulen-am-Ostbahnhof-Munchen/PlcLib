/*
 * Automation_THREE_POSITION.cpp
 *
 *  Created on: 18.11.2021
 *      Author: Franz
 */


#include <stdbool.h>
#include <stdint.h>
#include "Automation_THREE_POSITION.h"











void THREE_POSITION_SWITCH::operator ()(void) {

    /* any case */                                                 if(!I1 && !I2) {  State = THREE_POSITION_SWITCH_v1::Off;        return;                    }          //Off is Off. nothing else.
    switch (State) { /* in case */                                                                                                                                       //
    case THREE_POSITION_SWITCH_v1::Off:                            if( I1 && !I2) {  State = THREE_POSITION_SWITCH_v1::Momentary_forward_up_right;   Value2++; }         //if we was off, we go mom.
                                                                   if(!I1 &&  I2) {  State = THREE_POSITION_SWITCH_v1::Momentary_backward_down_left; Value2++; } break;  //if we was off, we go mom.
    case THREE_POSITION_SWITCH_v1::Momentary_forward_up_right:     if( I1       ) {  State = THREE_POSITION_SWITCH_v1::held_forward_up_right;                  } break;  // held
    case THREE_POSITION_SWITCH_v1::Momentary_backward_down_left:   if(        I2) {  State = THREE_POSITION_SWITCH_v1::held_backward_down_left;                } break;  // held
    case THREE_POSITION_SWITCH_v1::held_forward_up_right:          if(!I1       ) {  State = THREE_POSITION_SWITCH_v1::Off;                                    } break;  // only exit if Button is no more pressed.
    case THREE_POSITION_SWITCH_v1::held_backward_down_left:        if(       !I2) {  State = THREE_POSITION_SWITCH_v1::Off;                                    } break;  // only exit if Button is no more pressed.
    default:                                            {  State = THREE_POSITION_SWITCH_v1::Off;                                    } break;  // ERROR
    }

}

void THREE_POSITION_VALVE::operator ()(void) {

    switch (State){
    case THREE_POSITION_SWITCH_v1::Off:                             Q1 = false; Q2 = false; break;
    case THREE_POSITION_SWITCH_v1::Momentary_forward_up_right:      Q1 = true;  Q2 = false; break;
    case THREE_POSITION_SWITCH_v1::held_forward_up_right:           Q1 = true;  Q2 = false; break;
    case THREE_POSITION_SWITCH_v1::Momentary_backward_down_left:    Q1 = false; Q2 = true;  break;
    case THREE_POSITION_SWITCH_v1::held_backward_down_left:         Q1 = false; Q2 = true;  break;
    default:                                                        Q1 = false; Q2 = false; break;
    }


}




