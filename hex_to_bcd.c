/*
 * hex_to_bcd.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Thiago Gesteira
 */

//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------

#include "Include/hex_to_bcd.h"

//Local Vars.
unsigned char adc_char[4];
//Global Vars.
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

void HEXtoBCD(int hex_value){
    int value,i;
    for(i=0; i < 4; i++) {
        adc_char[i] = '0';
    }
    while (hex_value > 999){
        hex_value = hex_value - 1000;
        value = value + 1;
        adc_char[0] = 0x30 + value;
    }
    value = 0;
    while (hex_value > 99){
        hex_value = hex_value - 100;
        value = value + 1;
        adc_char[1] = 0x30 + value;
    }
    value = 0;
    while (hex_value > 9){
        hex_value = hex_value - 10;
        value = value + 1;
        adc_char[2] = 0x30 + value;
    }
    adc_char[3] = 0x30 + hex_value;
}
//-----------------------------------------------------------------
//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){
    int i;
    for(i=0; i < 4; i++) {
        display_line[line][i+location] = adc_char[i];
        update_display = 1;
        display_changed = 1;
    }
}

