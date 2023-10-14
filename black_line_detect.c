/*
 * black_line_detect.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Thiago Gesteira
 */

#include  "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"
#include  "Include\wheels.h"

// white <= 100; black >= 750
// forward when white, black, pause, turn right

//Global Vars. - always the first line? (FLAG)
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

// Added Global Vars.
extern unsigned volatile int wait;
volatile char state = WAIT;
extern unsigned volatile int ADC_Left_Detect_Global;
extern unsigned volatile int ADC_Right_Detect_Global;
extern unsigned volatile int ADC_Thumb_Global;
extern unsigned char delay_start;
unsigned char delay_time = RESET_STATE;
extern unsigned char event;

// Local Vars.
unsigned volatile int last_wait = RESET_STATE;

//Black Line
void run_till_black(void) {
switch(state){
     case WAIT: // Begin
         wait_case();
         break; //
     case START: // Begin
         start_case();
         break; //
     case RUN: //
         run_case_till_black();
         break;
     case RUN2:
         run_case_turn();
         break;
     case END: // End
         end_case();
         break; //
     default: break;
     }
}

void wait_case(void){
    if (last_wait != wait) { //copy of Time Sequence variable for wheel movement
        last_wait = wait;
        delay_time++; // every 1 sec
        //time_change = 1;
    }
    if(delay_time >= WAITING2START){ // delaying for 2 sec
        state = START;
    }
}
void run_case_till_black(void) {
    // while not white
    // white less than 300 | black greater than 6000
    if (ADC_Left_Detect_Global <= WHITE_BOUND && ADC_Right_Detect_Global <= WHITE_BOUND) {
        strcpy(display_line[0], "     -----");
        strcpy(display_line[1], "     WHITE");
        strcpy(display_line[2], "     FOUND");
        display_changed = 1;
        update_display =1 ;
        wheels_forward();
    }
    if (ADC_Left_Detect_Global >= BLACK_BOUND || ADC_Right_Detect_Global >= BLACK_BOUND) {
        strcpy(display_line[0], "     -----");
        strcpy(display_line[1], "     BLACK");
        strcpy(display_line[2], "     FOUND");
        display_changed = 1;
        update_display =1 ;
        wheels_stop();
        state = RUN2;
    }
}


void run_case_turn(void){
    turn_counter();
    if (last_wait != wait) { //copy of Time Sequence variable for wheel movement
            last_wait = wait;
            delay_time++; // every 1 sec
            //time_change = 1;
    }
    if(delay_time >= TRAVEL_DISTANCE){ // delaying for 2 sec
        state = END;
    }
}

void start_case(void){
    // wait 1 sec
    wheels_stop();
    delay_time = 0;
    state = RUN;
}
void end_case(void) {
    wheels_stop();
    event = NONE;
    state = WAIT;
}


