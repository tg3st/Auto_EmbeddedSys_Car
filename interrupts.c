/*
 * interrupts.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Thiago Gesteira
 */

#include  "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"

//Global Vars.
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern unsigned char time_change;
volatile char one_time;
extern char display_line[4][11];
unsigned volatile int wait = RESET_STATE; // equal to Time_Sequence

//Added Global Vars.
extern unsigned char event;

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
    wait++; // incremented every 100 ms
    // old_time_sequence reset every
    switch (wait) {
        case 2:
            display_changed = 1;
            update_display = 1;
            break;
        case 10: // every 1 second
            wait = 0;
            break;

        default: break;
    }
    // Time Sequence
     one_time = 1;

//----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
case 0: break; // No interrupt
case 2:
// ccr1 1
    P4IFG &= ~SW1;
    P4IE |= SW1;
    TB0CCTL1 &= ~CCIFG;
    TB0CCTL1 &= ~CCIE; // CCR1 disble interrupt
    TB0CCR1 += TB0CCR1_INTERVAL;
    break;
case 4:
// switch 2
    P2IFG &= ~SW2;
    P2IE |= SW2;
    TB0CCTL2 &= ~CCIFG;
    TB0CCTL2 &= ~CCIE; // CCR1 disble interrupt
    TB0CCR2 += TB0CCR2_INTERVAL;
    break;
case 14: // overflow
//...... Add What you need happen in the interrupt ......
break;
default: break;
}
//----------------------------------------------------------------------------
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB1 0 Interrupt handler
//----------------------------------------------------------------------------
    TB1CCR0 += TB1CCR0_INTERVAL; // Add Offset to TBCCR0

    TB1CCTL0 &= ~CCIFG;     // Clear CCR0 Flag
    TB1CCTL0 &= ~CCIE;      // Disable CCR0
    ADCCTL0 |= ADCSC;       //Start next ADC sample
    // Time Sequence
     one_time = 1;

//----------------------------------------------------------------------------
}

//Switches Local. Vars

// Port 4 interrupt. For switches, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.
#pragma vector=PORT4_VECTOR
__interrupt void switch_interrupt(void) {
// Switch 1
    if (P4IFG & SW1) {
        P4IE &= ~SW1; //Disable SW1 Interrupt
        P2IFG &= ~SW1; // Clear P2.6 Flag
        TB0CCTL1 |= CCIFG; // Clear CCR1 Flag
        TB0CCR1 = TB0R + SW_DEBOUNCE_TIME; //
        TB0CCTL1 |= CCIE; // Enable CCR1 Interrupt
        // do what u want
        strcpy(display_line[1], "     START");
        strcpy(display_line[2], "     BLACK");
        strcpy(display_line[2], "     DETECT");
        update_display = 1;
        display_changed = 1;
        event = BLACK_DETECT;
   }
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
// Switch 2
    if (P2IFG & SW2) {
        P2IE &= ~SW2;
        P2IFG &= ~SW2; // IFG SW2 cleared
        TB0CCTL2 |= CCIFG;
        TB0CCR2 = TB0R + SW_DEBOUNCE_TIME;
        TB0CCTL2 |= CCIE;
        // do what u want
        strcpy(display_line[1], "    SW2   ");
        strcpy(display_line[2], "   PRESS  ");
        update_display = 1;
        display_changed = 1;
    }
}




