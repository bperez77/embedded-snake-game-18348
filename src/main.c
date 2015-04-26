/* main.c
 *
 * ECE348, Spring 2015
 * Group C4
 * Brandon Perez bmperez
 * Rohit Banerjee rohitban
 *
 * Target: MC9S12C128
 * CodeWarrior Version: 5.1
 *
 * Created: Sat 25 Apr 2015 06:24:57 PM EDT
 * Last Modified: TODO: Update
 *
 * TODO: ENTER PROGRAM NAME HERE
 *
 * TODO: ENTER PROGRAM DESCRIPTION HERE
 *
 * TODO: ENTER IF THIS IS STANDALONE OR EXTERNALLY VISIBLE MODULES
 *
 * Pin Connections:
 *     TODO: ENTER PIN CONNECTION SETUP HERE
 */

// Freescale libraries
#include <hidef.h>
#include <mc9s12c128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12c128"

// 348 libraries
#include "modclock.h"
#include "lcd_lib.h"

// Project libraries
#include "setup.h"
#include "snake_game.h"

// The state of the snake game
static snake_game_t game;

/*----------------------------------------------------------------------------
 * Main Routine
 *----------------------------------------------------------------------------*/

int main()
{
    // Setup the clock and LCD
    clockSetup();
    lcdSetup();

    // Setup the ports, serial communication, PWM, A/D, and timer
    setup_ports();
    setup_serial();
    setup_pwm();
    setup_atd();
    setup_timer();

    // Initialize the game state
    game_init(&game);

    // Enable all interrupts
    EnableInterrupts;


    /* Loop forever, reading the user input, and updating the game
     * state appropiately. */
    for (;;)
    {
        // Check paused button

        // Check reset button

        // Display to the LCD's

        // Check if a board update cycle has happened
        // If so, update the paused state, or reset the game as per the presses
    }
}

/*----------------------------------------------------------------------------
 * Interrupts
 *----------------------------------------------------------------------------*/

void interrupt VectorNumber_Vsci sci_interrupt()
{
    // Acknowledge interrupt

    // Read out character sent
    // switch on character, check 'wasd'.
    // Queue direction to be updated if the input is valid.

    return;
}

void interrupt VectorNumber_Vatd0 atd_interrupt()
{
    // Acknowledge interrupt

    // Read out new value

    // Queue up brightness level to be updated

    return;
}

void interrupt VectorNumber_Vtimch7 tc7_interrupt()
{
    // Acknowledge interrupt

    // Increment internal (row, col), update port values

    // Increment updates

    // If # updates is board size (64), then move all "queued up"
    // values as the new values for the game (brightness, pause, etc.)

    return;
}
