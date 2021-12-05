/*
 * Automation_FOUR_POSITION.cpp
 *
 *  Created on: 18.11.2021
 *      Author: Franz
 */


#include <stdbool.h>
#include <stdint.h>
#include "Automation_FOUR_POSITION.h"











void FOUR_POSITION_SWITCH::operator ()(void) {

    /* any case */                                                if(!I1 && !I2 && !I3) {  State = FOUR_POSITION_SWITCH_v1::Off;        return;                     }         //Off is Off. nothing else.
    switch (State) { /* in case */                                                                                                                                            //
    case FOUR_POSITION_SWITCH_v1::Off:                            if( I1 && !I2 && !I3) {  State = FOUR_POSITION_SWITCH_v1::Momentary_forward_up_right;   Value2++; }         //if we was off, we go mom.
                                                                  if(!I1 &&  I2 && !I3) {  State = FOUR_POSITION_SWITCH_v1::Momentary_backward_down_left; Value2++; }         //if we was off, we go mom.
                                                                  if(!I1 && !I2 &&  I3) {  State = FOUR_POSITION_SWITCH_v1::Momentary_float;              Value2++; } break;  //if we was off, we go mom.
    case FOUR_POSITION_SWITCH_v1::Momentary_forward_up_right:     if( I1              ) {  State = FOUR_POSITION_SWITCH_v1::held_forward_up_right;                  } break;  // held
    case FOUR_POSITION_SWITCH_v1::Momentary_backward_down_left:   if(        I2       ) {  State = FOUR_POSITION_SWITCH_v1::held_backward_down_left;                } break;  // held
    case FOUR_POSITION_SWITCH_v1::Momentary_float:                if(               I3) {  State = FOUR_POSITION_SWITCH_v1::held_float;                             } break;  // held
    case FOUR_POSITION_SWITCH_v1::held_forward_up_right:          if(!I1              ) {  State = FOUR_POSITION_SWITCH_v1::Off;                                    } break;  // only exit if Button is no more pressed.
    case FOUR_POSITION_SWITCH_v1::held_backward_down_left:        if(       !I2       ) {  State = FOUR_POSITION_SWITCH_v1::Off;                                    } break;  // only exit if Button is no more pressed.
    case FOUR_POSITION_SWITCH_v1::held_float:                     if(              !I3) {  State = FOUR_POSITION_SWITCH_v1::Off;                                    } break;  // only exit if Button is no more pressed.

    default:                                            {  State = FOUR_POSITION_SWITCH_v1::Off;                                    } break;  // ERROR
    }

}

void VALVE_WITH_FLOAT::operator ()(void) {

    switch (State){
    case FOUR_POSITION_SWITCH_v1::Off:                             Q1 = false; Q2 = false; Q3 = false; Q4 = false; break;
    case FOUR_POSITION_SWITCH_v1::Momentary_forward_up_right:      Q1 = true;  Q2 = false; Q3 = true;  Q4 = true;  break;
    case FOUR_POSITION_SWITCH_v1::held_forward_up_right:           Q1 = true;  Q2 = false; Q3 = true;  Q4 = true;  break;
    case FOUR_POSITION_SWITCH_v1::Momentary_backward_down_left:    Q1 = false; Q2 = true;  Q3 = true;  Q4 = true;  break;
    case FOUR_POSITION_SWITCH_v1::held_backward_down_left:         Q1 = false; Q2 = true;  Q3 = true;  Q4 = true;  break;
    case FOUR_POSITION_SWITCH_v1::Momentary_float:                 Q1 = false; Q2 = false; Q3 = true;  Q4 = true;  break;
    case FOUR_POSITION_SWITCH_v1::held_float:                      Q1 = false; Q2 = false; Q3 = true;  Q4 = true;  break;
    default:                                                       Q1 = false; Q2 = false; Q3 = false; Q4 = false; break;
    }


}
