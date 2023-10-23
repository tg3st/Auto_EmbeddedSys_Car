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
unsigned volatile int delay_time = RESET_STATE;
extern unsigned char event;

// Local Vars.
unsigned volatile int last_wait = RESET_STATE;

//Black Line
void run_till_black(void) {
switch(state){
     case WAIT: // Wait for a couple seconds after
         wait_case();
         break; //
     case START: // Reset delay variable
         start_case();
         break;
     case RUN: // Run car until black line is found
         run_case_till_black();
         break;
     case TURNR: // Turn to align with black line
         run_case_turn_left();
         break;
     case ON_LINE: // Run along black line
         run_case_on_line();
         break;
     case TO_MIDDLE:
         run_case_to_middle();
         break;
     case END: // End
         end_case();
         break; //
     default: break;
     }
}

void wait_case(void){
    if (last_wait != wait) { //copy of Time Sequence variable for wheel movement && FLAG - make this a function
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
    if (ADC_Right_Detect_Global >= BLACK_BOUND || ADC_Left_Detect_Global >= BLACK_BOUND) {
        strcpy(display_line[0], "     -----");
        strcpy(display_line[1], "     BLACK");
        strcpy(display_line[2], "     FOUND");
        strcpy(display_line[3], "  turnLEFT");
        display_changed = 1;
        update_display =1 ;
        wheels_stop();
        delay_time = 0;
        state = TURNR;
    }
}



void run_case_turn_left(void){

    if (last_wait != wait) { //copy of Time Sequence variable for wheel movement - TURN INTO FUNCTION
        last_wait = wait;
        delay_time++; // every 1 sec
    }
    if(delay_time >= TURN_STOP_TIME) {
        turn_clockwise();
        if(ADC_Left_Detect_Global >= LIBERAL_BLACK_BOUND){
            wheels_stop();
            delay_time = 0;
            state = ON_LINE; // on line code
        }
    }
}

void run_case_on_line(void) {
    //end
    strcpy(display_line[0], "     -----");
    strcpy(display_line[1], "       ON ");
    strcpy(display_line[2], "      LINE");
    strcpy(display_line[3], "     -----");
    // ADD run straight while on black line
    if (last_wait != wait) { //copy of Time Sequence variable for wheel movement - TURN INTO FUNCTION
            last_wait = wait;
            delay_time++; // every 1 sec
        }
        if(delay_time >= TURN_STOP_TIME) {
            strcpy(display_line[3], "     MOVE ");
            if (delay_time >= CIRCLE_TRAVEL_COUNT*2) {
                delay_time = 0;
                state = TO_MIDDLE;
            }
                if (ADC_Left_Detect_Global >= BLACK_BOUND && ADC_Right_Detect_Global >= BLACK_BOUND) {
                    LEFT_FORWARD_SPEED = PERCENT_10;
                    RIGHT_FORWARD_SPEED = PERCENT_10;
                }

                // Get back to line / Stay on line
                if (ADC_Right_Detect_Global <= WHITE_BOUND) {
                    // turn_left_on_line();
                    LEFT_FORWARD_SPEED = WHEEL_OFF;
                    RIGHT_FORWARD_SPEED = PERCENT_5;
                }
                if (ADC_Left_Detect_Global <= WHITE_BOUND) {
                    // turn_right_on_line();
                    RIGHT_FORWARD_SPEED = WHEEL_OFF;
                    LEFT_FORWARD_SPEED = PERCENT_5;
                }
                else {
                    LEFT_FORWARD_SPEED = PERCENT_10;
                    RIGHT_FORWARD_SPEED = PERCENT_5;
                }

            }
}

void run_case_to_middle(void) {
    strcpy(display_line[0], "     -----");
    strcpy(display_line[1], "       TO ");
    strcpy(display_line[2], "    MIDDLE");
    strcpy(display_line[3], "     -----");
    if (last_wait != wait) { //copy of Time Sequence variable for wheel movement - TURN INTO FUNCTION
        last_wait = wait;
        delay_time++; // every 1 sec
    }
    if(delay_time >= WAITING2START) {
        turn_clockwise();
        if(delay_time >= 15){
            wheels_stop();
            wheels_forward();
            if (delay_time >= 30) {
                wheels_stop();
                state = END;
            }
        }
    }
}

void start_case(void){
    wheels_stop();
    delay_time = 0;
    state = RUN;
}
void end_case(void) {
    strcpy(display_line[0], "     -----");
    strcpy(display_line[1], "      THE ");
    strcpy(display_line[2], "      END ");
    strcpy(display_line[3], "     -----");
    wheels_stop();
    event = NONE;
    state = WAIT;
}


