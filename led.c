//
// Created by Thiago Gesteira on 9/13/2023.
// Description: File for LED initialization
//
#include  "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"

void Init_LEDs(void);

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
    P1OUT &= ~RED_LED;
    P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}