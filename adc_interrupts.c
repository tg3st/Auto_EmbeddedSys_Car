/*
 * adc_interrupts.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Thiago Gesteira
 */

#include  "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"


//Local Vars.
unsigned char ADC_Channel;
unsigned volatile int ADC_Left_Detect;
unsigned volatile int ADC_Right_Detect;
unsigned volatile int ADC_Thumb;
unsigned volatile int ADC_Left_Detect_Global = RESET_STATE;
unsigned volatile int ADC_Right_Detect_Global = RESET_STATE;
unsigned volatile int ADC_Thumb_Global = RESET_STATE;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
                        // before its previous conversion result was read.
            break;
        case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
            break;
        case ADCIV_ADCHIIFG: // Window comparator interrupt flags
            break;
        case ADCIV_ADCLOIFG: // Window comparator interrupt flag
            break;
        case ADCIV_ADCINIFG: // Window comparator interrupt flag
            break;
        case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
            adc_thumb();
            break;
        default:
            break;
    }
}

void adc_thumb(void){
    ADCCTL0 &= ~ADCENC; // Disable ENC bit.
    switch (ADC_Channel++){
        case 0x00: // Channel A2 Interrupt
            ADC_Left_Detect = ADCMEM0; // Move result into Global Values

            ADC_Left_Detect_Global = ADC_Left_Detect >> 2; // Divide result by 4
            HEXtoBCD(ADC_Left_Detect_Global); // Convert to str
            adc_line(0,0); // Place String in Display

            ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
            ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
            ADCCTL0 |= ADCSC; // Start next sample // Change placement of statement - FLAG
            break;
        case 0x01: // Channel A3 Interrupt
            ADC_Right_Detect = ADCMEM0; // Move result into Global Values

            ADC_Right_Detect_Global = ADC_Right_Detect >> 2; // Divide result by 4
            HEXtoBCD(ADC_Right_Detect_Global); // Convert to str
            adc_line(1,0); // Place String in Display

            ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
            ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
            ADCCTL0 |= ADCSC; // Start next sample // Change placement of statement - FLAG
            break;

        // add break count for thumb wheel reeding
        // add count for number of reading - FLAG
        case 0x02: // Channel A5 Interrupts // thumb_wheel is first one???
            ADC_Thumb = ADCMEM0; // Move result into Global Values

            ADC_Thumb_Global = ADC_Thumb >> 2; // Divide result by 4
            HEXtoBCD(ADC_Thumb); // Convert to str
            adc_line(2,0); // Place String in Display

            ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
            ADCMCTL0 |= ADCINCH_2; // Enable First channel A2

            TB1CCTL0 |= CCIE;
            TB1CCR0 = TB1R + TB1CCR0_INTERVAL;

            ADC_Channel=0;

            break;
        default:
            break;
    }
    ADCCTL0 |= ADCENC; // Enable Conversions
}

