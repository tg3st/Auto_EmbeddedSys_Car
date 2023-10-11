//
// Created by Thiago Gesteira on 9/13/2023.
// Description: File for proper port initializations
//

#include "msp430.h"
#include  <string.h>
#include  "Include\functions.h"
#include  "Include\LCD.h"
#include  "Include\macros.h"
#include  "Include\ports.h"

void Init_Ports(void){
    Init_Port1();
    Init_Port2();
    Init_Port3();
    Init_Port4();
    Init_Port5();
    Init_Port6();
}

void Init_Port1 (void) { // Configure PORT 1

    P1OUT = 0x00; // P1 set Low
    P1DIR = 0x00; // Set P1 direction to output

//Pin 1.0 - FLAG
    P1SEL0 & ~RED_LED; // RED_LED GPIO operation
    P1SEL1 &= ~RED_LED; // RED_LED GPIO operation
    //P1OUT &= ~RED_LED; // INIT VAL. = low / off
    P1DIR &= ~RED_LED; // Direction = in

//Pin 1.1
    P1SEL0 |= A1_SEEED; //
    P1SEL1 |= A1_SEEED; //

//Pin 1.2
    P1SEL0 |= V_DETECT_L; //
    P1SEL1 |= V_DETECT_L; //

//Pin 1.3
    P1SEL0 |= V_DETECT_R; //
    P1SEL1 |= V_DETECT_R; //

//Pin 1.3
    P1SEL0 |= V_DETECT_R; //
    P1SEL1 |= V_DETECT_R; //

//Pin 1.4
    P1SEL0 |= A4_SEEED; //
    P1SEL1 |= A4_SEEED; //

//Pin 1.5
    P1SEL0 |= V_THUMB; //
    P1SEL1 |= V_THUMB;  //

//Pin 1.6
    P1SEL0 |= UCA0RXD; //
    P1SEL1 &= ~UCA0RXD;  //

//Pin 1.7
    P1SEL0 |= UCA0TXD; //
    P1SEL1 &= ~UCA0TXD;  //
}

void Init_Port2 (void) { // Configure PORT 2

    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to output

//Pin 2.0
    P2SEL0 & ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2SEL1 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2OUT &= ~SLOW_CLK; // Initial Value = Low / Off
    P2DIR |= SLOW_CLK; // Direction = output

//Pin 2.1
    P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2OUT &= ~CHECK_BAT;  // Initial Value = Low / Off
    P2DIR |= CHECK_BAT; // Direction = output

//Pin 2.2
    P2SEL0 &= ~IR_LED; // USCI A1 UART operation
    P2SEL1 &= ~IR_LED; // USCI_A1 UART operation
    P2OUT &= ~IR_LED; // Initial val = Low / Off
    P2DIR |= IR_LED; // Direction = output

//Pin 2.3
    P2SEL0 &= ~SW2; // SW2 set as I/0
    P2SEL1 &= ~SW2; // SW2 set as I/0
    P2DIR &= ~SW2; // SW2 Direction = input
    P2PUD |= SW2; // Configure pull-up resistor SW2
    P2REN |= SW2; // Enable pull-up resistor SW2
    P2IES |= SW2; // SW2 Hi/Lo edge interrupt
    P2IFG &= ~SW2; // IFG SW2 cleared
    P2IE |= SW2; // SW1 interrupt Enabled

//Pin 2.4
    P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO
    P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO
    P2OUT &= ~IOT_RUN_RED; // Initial val = Low / Off
    P2DIR |= IOT_RUN_RED; // Direction = input

//Pin 2.5
    P2SEL0 & ~DAC_ENB; // DAC_ENB GPIO
    P2SEL1 &= ~DAC_ENB;  // DAC_ENB GPIO
    P2OUT |= DAC_ENB; // Initial Value = high
    P2DIR |= DAC_ENB; // Direction = output

//Pin 2.6
    P2SEL0 &= ~LFXOUT; // LFXOUT CLock Operation
    P2SEL1 |= LFXOUT;  // LFXOUT CLock Operation

//Pin 2.7
    P2SEL0 &= ~LFXIN; // LFXIN CLock Operation
    P2SEL1 |= LFXIN;  // LFXIN CLock Operation
}

void Init_Port3 (void) { // Configure PORT 3

    P3OUT = 0x00; // P3 set Low
    P3DIR = 0x00; // Set P3 direction to output

//Pin 3.0 - FLAG (NO OUT?)
    P3SEL0 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3SEL1 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    //P3OUT &= ~TEST_PROBE; // INIT VAL. = low / off
    P3DIR &= ~TEST_PROBE; // Direction = input

//Pin 3.1
    P3SEL0 |= OA2O; // OA2O GPIO operation
    P3SEL1 |= OA2O; // OA2O GPIO operation

//Pin 3.2
    P3SEL0 |= OA2N; //
    P3SEL1 |= OA2N; //

//Pin 3.3
    P3SEL0 |= OA2P; // Photodiode Operation
    P3SEL1 |= OA2P; // Photodiode Operation

//Pin 3.4 - FLAG (NO OUT?)
    P3SEL0 &= ~SMCLK; // SMCLK operation
    P3SEL1 &= ~SMCLK; // SMCLK operation
    //P3OUT &= ~SMCLK; // set I=0
    P3DIR &= ~SMCLK; // set direction to output

//Pin 3.5
    P3SEL0 |= DAC_CNTL; //
    P3SEL1 |= DAC_CNTL; //

//Pin 3.6
    P3SEL0 |= IOT_LINK_GRN; //
    P3SEL1 |= IOT_LINK_GRN; //

//Pin 3.7
    P3SEL0 |= IOT_EN; //
    P3SEL1 |= IOT_EN; //
}
void Init_Port4(void) { // Configure PORT 4
//------------------------------------------------------------------------------
    P4OUT = 0x00; // P4 set Low
    P4DIR = 0x00; // Set P4 direction to output

    // Pin 4.0
    P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4OUT &= ~RESET_LCD; // Initial Value = Low / Off
    P4DIR |= RESET_LCD; // Direction = output (ASK TA ABOUT IN VS OUT W/ 0)

    // Pin 4.1
    P4SEL0 &= ~SW1; // SW1 set as I/0
    P4SEL1 &= ~SW1; // SW1 set as I/0
    P4DIR &= ~SW1; // SW1 Direction = input
    P4PUD |= SW1; // Configure pull-up resistor SW1
    P4REN |= SW1; // Enable pull-up resistor SW1
    P4IES |= SW1; // SW1 Hi/Lo edge interrupt
    P4IFG &= ~SW1; // IFG SW1 cleared
    P4IE |= SW1; // SW1 interrupt Enabled

    // Pin 4.2
    P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

    // Pin 4.3
    P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

    // Pin 4.4
    P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
    P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

    // Pin 4.5
    P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
    P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

    // Pin 4.6
    P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
    P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

    // Pin 4.7
    P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
    P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
}

void Init_Port5(void) { // Configure PORT 5
//------------------------------------------------------------------------------
    P5OUT = 0x00; // P5 set Low
    P5DIR = 0x00; // Set P5 direction to output

    // Pin 5.0
    P5SEL0 |= V_BAT; //
    P5SEL1 |= V_BAT; //

    // Pin 5.1
    P5SEL0 |= V_5_0; //
    P5SEL1 |= V_5_0; //

    // Pin 5.2
    P5SEL0 |= V_DAC; //
    P5SEL1 |= V_DAC; //

    // Pin 5.3
    P5SEL0 |= V_3_3; //
    P5SEL1 |= V_3_3; //

    // Pin 5.4
    P5SEL0 &= ~IOT_BOOT; //
    P5SEL1 &= ~IOT_BOOT; //
    //P5OUT &= ~IOT_BOOT; //
    P5DIR &= ~IOT_BOOT; //
}

void Init_Port6(void) { // Configure PORT 6
//------------------------------------------------------------------------------
    P6OUT = 0x00; // P6 set Low
    P6DIR = 0x00; // Set P6 direction to output

    // Pin 6.0 - FLAG (ASSUME INIT 0)
    P6SEL0 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
    P6SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
    P6OUT |= LCD_BACKLITE;
    P6DIR |= LCD_BACKLITE; // Direction = output

    // Pin 6.1 - FLAG
    P6SEL0 |= R_FORWARD; //
    P6SEL1 &= ~R_FORWARD; //
    P6DIR |= R_FORWARD; // Direction = output

    // Pin 6.2 - FLAG
    P6SEL0 |= R_REVERSE; //
    P6SEL1 &= ~R_REVERSE; //
    P6DIR |= R_REVERSE; // Direction = input

    // Pin 6.3 - FLAG
    P6SEL0 |= L_FORWARD; //
    P6SEL1 &= ~L_FORWARD; //
    P6DIR |= L_FORWARD; // Direction = output

    // Pin 6.4 - FLAG
    P6SEL0 |= L_REVERSE; //
    P6SEL1 &= ~L_REVERSE; //
    P6DIR |= L_REVERSE; // Direction = input

    // Pin 6.5 - FLAG
    P6SEL0 &= ~P6_5;
    P6SEL1 &= ~P6_5;
    //P6OUT &= ~P6_5;
    P6DIR &= ~P6_5; // Direction = input

    // Pin 6.6
    P6SEL0 &= ~GRN_LED;
    P6SEL1 &= ~GRN_LED;
    P6DIR &= ~GRN_LED; // Direction = input
}
