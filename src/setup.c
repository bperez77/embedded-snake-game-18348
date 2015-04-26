/* setup.c
 *
 * ECE348, Spring 2015
 * Group C4
 * Brandon Perez bmperez
 * Rohit Banerjee rohitban
 *
 * Target: MC9S12C128
 * CodeWarrior Version: 5.1
 *
 * Created: Sat 25 Apr 2015 06:26:40 PM EDT
 * Last Modified: TODO: Update
 *
 * This file is responsible for setting up all the necessary settigngs on the
 * project board to ensure the correct operation of the snake game. This
 * includes setting up the ports, serial module, PWM module, A/D converter,
 * and the timer module.
 *
 * Externally Visible Items:
 *     void setup_ports()
 *     void setup_serial()
 *     void setup_pwm()
 *     void setup_atd()
 *     void setup_timer()
 */

#include <hidef.h>         /* common macros and defines */
#include <mc9s12c128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c128"

/*----------------------------------------------------------------------------
 * Internal Definitions
 *----------------------------------------------------------------------------*/

// Clock dividers for the A/D converter, serial module, and PWM module
#define PWM_CLOCK_SCALE                4
#define ATD_CLOCK_SCALE                5
#define TIMER_CLOCK_SCALE              4
#define SCI_CLOCK_SCALE               52

// The value of the timer to generate an interrupt for (every 15 ms)
#define TIMER_TC7_CMP               7500

/*----------------------------------------------------------------------------
 * Interface Functions
 *----------------------------------------------------------------------------*/

/* setup_ports
 *
 * Configures the ports on the MCU appropiately for this project. See
 * the comments below for the specific configurations.
 *
 * Port T[7:5] drives the column of the LED matrix, T[4:2] the row. Port P[0]
 * outputs the PWM signal that drives the LED's. Port AD[7] is the analog input
 * of the measured ambient brightness of the room. Port B[0] is the pause button
 * input, and Port B[1] is the restart button input.
 */
void setup_ports()
{
    /* Port T[7:2] is used to drive the row and column numbers out to the two
     * decoders that are hooked up to the LED matrix. This specifies which LED
     * is currently lit up. Port T[7:5] is the column and T[4:02 is the row. */
    DDRT = 0xFC;            // Port T[7:2] are outputs

    /* Port P[0] outputs the PWM signal to the LED matrix, which is the enable
     * signal into the decoder. This controls the brightness of the LED's. */
    DDRP_DDRP0 = 0x1;       // Port P[0] is an output
    MODRR_MODRR0 = 0x1;     // Port P[0] is a PWM port

    /* Port AD[7] is the input for the analog source that controls
     * how bright the LED's are. This is a photodiode circuit that detects
     * the ambient light in the room. */
    ATDDIEN_IEN7 = 0xFC;    // Port AD[7] is an analog port
    DDRAD_DDRAD7 = 0x00;    // Port AD[7] is an input port

    /* Port B[0] is connected to PB[0], which is the pause input for the game.
     * This toggles whether or not the game is paused. Port B[1] is connected
     * to PB[1], which is the restart input for the game. This restarts the
     * game to its initial state. */
    DDRB_BIT0 = 0x0;        // Port B[1:0] are inputs
    DDRB_BIT1 = 0x0;

    return;
}

/* setup_serial
 *
 * Configures the serial module on the board to properly communicate
 * with the desktop computer.
 *
 * The serial communication is only one-way, the computer transmitting to the
 * board, so only the receiver is enabled. The receiver module generates an
 * interrupt upon receiving a new message. The message format is an 8-bit UART
 * format. The baud rate is 9600.
 */
void setup_serial()
{
    SCICR2_RE = 0x1;            // Enable the receiver
    SCICR2_RIE= 0x1;            // Enable receiver interrupts

    SCICR1_PE = 0x0;            // Disable parity checking
    SCICR1_M = 0x0;             // Set the data format as 1 start-bit, 8 data
                                // bits, and one stop bit

    SCIBD = SCI_CLOCK_SCALE;    // Set the baud rate to 38400

    return;
}

/* setup_pwm
 *
 * Configures the PWM module on the board appropiately for this project.
 *
 * The PWM is setup to output over channel 0 (Port P[0]). The PWM signal is
 * positive polarity, with a frequency of 0.5 Mhz (divided from the onboard
 * clock). The PWM is left-aligned, and we don't concatenate it with channel 1.
 * Thus the PWM duty cycle has 8-bit resolution.
 */
void setup_pwm()
{
    PWME_PWME0 = 1;                     // Enable PWM Channel 0
    PWMPOL_PPOL0 = 1;                   // Positive polarity

    PWMCLK_PCLK0 = 0;                   // Choose clock A
    PWMPRCLK_PCKA = PWM_CLOCK_SCALE;    // Set the clock frequency to 0.5 Mhz
                                        // (bus clock / 16)

    PWMCAE_CAE0 = 0;                    // Left aligned PWM
    PWMCTL_CON01 = 0;                   // No concatenation

    return;
}

/* setup_atd
 *
 * Configures the A/D converter on the module appropiately for the project.
 *
 * The A/D converter generates interrupts upon completion. The FIFO feature is
 * disabled, so there is simply a 1-register buffer. There is only one A/D
 * converter used, so we setup a sequence of length 1.
 */
void setup_atd()
{
    ATDCTL2_ADPU = 1;               // Turn on the A/D converter
    ATDCTL2_ASCIE = 1;              // Enable interrupt on conversion completion
    ATDCTL3_FRZ  = 2;               // Finish current conversion then freeze

    ATDCTL5_MULT = 0;               // Single channel A/D conversion
    ATDCTL3_S8C = 0;                // Set sequence length to 1
    ATDCTL3_S4C = 0;
    ATDCTL3_S2C = 0;
    ATDCTL3_S1C = 1;
    ATDCTL5_CC = 0;                 // Start sequence at channel 0
    ATDCTL5_CB = 0;
    ATDCTL5_CA = 0;

    ATDCTL4_SRES8 = 1;              // 8 bit resolution
    ATDCTL4_PRS = ATD_CLOCK_SCALE;  // ATDclock = 666,666Hz
    ATDCTL4_SMP = 0;                // Phase 2 sample time is 2 ATD clock
                                    // periods

    ATDCTL3_FIFO = 0;               // FIFO disabled
    ATDCTL5_DJM = 0;                // Left justified data storage
    ATDCTL5_DSGN = 0;               // Unsigned data representation
    ATDCTL5_SCAN = 1;               // Continuous conversion squences

    return;
}

/* setup_timer
 *
 * Configures the timer on the module appropiately for this project.
 *
 * The timer is configured to genreate an update every 15 ms. This is slightly
 * above what a person's persistance of vision (POV) is for light. Every timer
 * interrupt, the next LED on the matrix is driven, and is held for the timer's
 * period. Timer channel 7 is used to compare the value corresponding to 15 ms,
 * and the timer is reset whenever it reaches the specified value.
 */
void setup_timer()
{
    TSCR1_TEN = 1;                  // Enable the timer
    TSCR1_TSFRZ = 1;                // Disable in freeze mode (for debugging)
    // FIXME?
    TSCR1_TSWAI = 1;                // Disable in wait mode

    TSCR2_PR = TIMER_CLOCK_SCALE;   // Set the clock frequency to 0.5 Mhz
                                    // (bus clock / 16)

    TIOS_IOS7 = 1;                  // Enbale timer channel 7 output compare
    TSCR2_TCRE = 1;                 // Reset timer on successful compare
    TIE_C7I = 1;                    // Interrupt on successful compare
    TC7 = TIMER_TC7_CMP;            // Generate an interrupt every 15 ms

    return;
}

