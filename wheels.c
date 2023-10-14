//
// Created by Thiago Gesteira on 9/13/2023.
// Description: File for basic wheel functions and logic
//

#include  "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"
#include  "Include\wheels.h"

// Global Vars.

// Local Vars.

// INCLUDE ALL VARIABLES NEEDED


void turn_clockwise(){ // turns clockwise
    Lwheel_forward();
    Rwheel_reverse();
}

void turn_counter(){ // turns clockwise
    Lwheel_reverse();
    Rwheel_forward();
}

void Rwheel_forward(){ // turns right wheel forward off before right wheel reverse on
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    RIGHT_FORWARD_SPEED = PERCENT_20;
}
void Lwheel_forward(){ // turns left wheel forward off before left wheel reverse on
    LEFT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = PERCENT_80; //
}

void wheels_forward(){ // function definition for straight forward wheel movement
    wheels_stop();
    Lwheel_forward(); // turns left wheel forward on
    Rwheel_forward(); // turns right wheel forward on
}
void Rwheel_reverse(){ // turns right wheel forward off before right wheel reverse on
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = PERCENT_80; // RIGHT_REVERSE_SPEED = WHEEL_OFF;
}
void Lwheel_reverse(){ // turns left wheel forward off before left wheel reverse on
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = PERCENT_80;
}
void wheels_reverse(){ // sets both wheels to reverse
    wheels_stop();
    Rwheel_reverse();
    Lwheel_reverse();
}

void wheels_stop(){ // function definition for stopping wheels
    RIGHT_REVERSE_SPEED = WHEEL_OFF; // turn off left wheel
    LEFT_REVERSE_SPEED = WHEEL_OFF; // turn off right wheels
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
}
