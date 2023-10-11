/*
 * patterns.c
 *
 *  Created on: Sep 18, 2023
 *      Author: Thiago Gesteira
 */

#include  "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"
#include  "Include\wheels.h"

//Function Declarations
void run_straight(void);
void run_case_straight(void);
void wait_case(void);
void start_case(void);
void end_case(void);

//Global Vars.
extern unsigned char time_change;
extern unsigned char event;

//Local Vars.
unsigned char state = WAIT;
unsigned int segment_count;
unsigned int delay_start;

//Func. Defs.


void run_straight() {
    switch(state){
     case WAIT: // Begin
         wait_case();
         break; //
     case START: // Begin
         start_case();
         break; //
     case RUN: //
         wheels_forward();
         //run_case_straight();
         break; //
     case END: // End
         end_case();
         break; //
     default: break;
     }
}

void wait_case(void){
    if(time_change){
        time_change = 0;
        if(delay_start++ >= WAITING2START){
            delay_start = 0;
            state = START;
        }
    }
}

void start_case(void){
     segment_count = 0;
     state = RUN;
}

void end_case(void) {
    wheels_stop();
    state = WAIT;
    event = NONE;
}

