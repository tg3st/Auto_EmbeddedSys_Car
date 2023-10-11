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

//Local Vars.
unsigned volatile long int wait = RESET_STATE; // equal to Time_Sequence
extern unsigned char state;
unsigned volatile char blink_count = RESET_STATE;




// FLAG - TIMER A0?
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
    wait++;
    // old_time_sequence reset every second
    switch (wait) {
        case 2:
            display_changed = 1;
            update_display = 1;
            break;
        case 250:
           // wait = 0;
            break;
        default: break;
    }
    if(blink_count++ > 10){
        blink_count = 0; // Reset for next count
        P6OUT ^= LCD_BACKLITE; // Flip State of LCD_BACKLITE
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
        strcpy(display_line[1], "    SW1   ");
        strcpy(display_line[2], "   PRESS  ");
        update_display = 1;
        display_changed = 1;
        P6OUT &= ~LCD_BACKLITE;
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
        P6OUT |= LCD_BACKLITE;
    }
}


