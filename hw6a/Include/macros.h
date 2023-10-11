//
// Created by Thiago Gesteira on 9/13/2023.
//

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //
#define CHAR1 ('1')
#define CHAR0 ('0')

// STATES ======================================================================
#define NONE ('N')
#define STRAIGHT ('L')

#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define RUN2 ('2')
#define END ('E')

// SWITCHES ======================================================================
#define PRESSED (0)
#define NOT_OKAY (0)
#define SW_DEBOUNCE_TIME (31250)
#define OKAY (1)
#define DEBOUNCE_RESTART (0)
#define RELEASED (1)

// TIMERS & INTERRUPTS ===========================================================
#define DIVS (0x0030)
#define DIVS_L (0x0030)
#define DIVS0 (0x0010)
#define DIVS0_L (0x0010)
#define DIVS1 (0x0020)
#define DIVS1_L (0x0020)
#define DIVS_0 (0x0000) // /1
#define DIVS_1 (0x0010) // /2
#define DIVS_1_L (0x0010)
#define DIVS_2 (0x0020) // /4
#define DIVS_2_L (0x0020)
#define DIVS_3 (0x0030) // /8
#define DIVS_3_L (0x0030)
#define DIVS__1 (0x0000) // /1
#define DIVS__2 (0x0010) // /2
#define DIVS__2_L (0x0010)
#define DIVS__4 (0x0020) // /4
#define DIVS__4_L (0x0020)
#define DIVS__8 (0x0030) // /8
#define DIVS__8_L (0x0030)
#define TB0CCR0_INTERVAL (50000) // 8,000,000 / 2 / 8 / (1 / 5msec)
#define TB0CCR1_INTERVAL (25000)
#define TB0CCR2_INTERVAL (25000)
#define FIFTY_MS_COUNT (25000)

// PWMs
#define PWM_PERIOD (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_FORWARD_SPEED (TB3CCR4)
#define LEFT_REVERSE_SPEED (TB3CCR5)
#define WHEEL_OFF (0)
#define SLOW (20000)
#define FAST (50000)
#define PERCENT_100 (50000)
#define PERCENT_80 (40000)
#define PERCENT_20 (10000)

//LCD
#define LCD_OFF (0);

// Main While loop switch cases
#define Time_Sequence_Rate (50) // 50 millisecods
#define S1250 (1250/Time_Sequence_Rate) // 1.25 seconds
#define S1000 (1000/Time_Sequence_Rate) // 1 second
#define S750 (750/Time_Sequence_Rate) // 0.75 seconds
#define S500 (500/Time_Sequence_Rate) // 0.50 seconds
#define S250 (250/Time_Sequence_Rate) // 0.25 seconds

// ID Dividers
#define ID_1 (0x0040) /* /2 */
#define ID_2 (0x0080) /* /4 */
#define ID_3 (0x00c0) /* /8 */
#define ID__2 (0x0040) /* /2 */
#define ID__4 (0x0080) /* /4 */
#define ID__8 (0x00c0) /* /8 */

//TAIDEX bit divider
#define TBIDEX_0 (0x0000) /* Divide by 1 */
#define TBIDEX_1 (0x0001) /* Divide by 2 */
#define TBIDEX_2 (0x0002) /* Divide by 3 */
#define TBIDEX_3 (0x0003) /* Divide by 4 */
#define TBIDEX_4 (0x0004) /* Divide by 5 */
#define TBIDEX_5 (0x0005) /* Divide by 6 */
#define TBIDEX_6 (0x0006) /* Divide by 7 */
#define TBIDEX_7 (0x0007) /* Divide by 8 */

#define TBIDEX__1 (0x0000) /* Divide by 1 */
#define TBIDEX__2 (0x0001) /* Divide by 2 */
#define TBIDEX__3 (0x0002) /* Divide by 3 */
#define TBIDEX__4 (0x0003) /* Divide by 4 */
#define TBIDEX__5 (0x0004) /* Divide by 5 */
#define TBIDEX__6 (0x0005) /* Divide by 6 */
#define TBIDEX__7 (0x0006) /* Divide by 7 */
#define TBIDEX__8 (0x0007) /* Divide by 8 */

// Changt prober
#define CHANGE_PROBE (P3OUT ^ TEST_PROBE)// Change state of Probes

// PORTS
#define P4PUD (P4OUT)
#define P2PUD (P2OUT)

