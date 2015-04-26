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
 * Snake Game
 *
 * This project is a simple implementation of a snake game for the MC9S12C128
 * Freescale module. The game runs on an 8x8 LED matrix on the project board,
 * and is fully controlled by the module. The module outputs row and column
 * numbers to two decoders, which drive a single LED at a time. The column
 * decocder enable is driven by the module's PWM signal, to control the
 * brightness of the LED's. The row enable serves to activate a single row.
 * A photodiode measures the current ambient brightness of the room, and that
 * is used to determine the duty cycle of the PWM signal, controlling the
 * brightness.
 *
 * The snake game goes by the standard rules. The snake attempts to eat as many
 * food pieces on the board as it can. Each time a food is eaten, the score
 * increases by 1, as does the size of the snake. This game has no walls on the
 * board, so the snake can wrap around the board. The game ends whenever the
 * snake intersects with itself. The game is controlled via a serial interface
 * with the computer. The computer can change the direction of the snake with
 * the old fashion directional controls: 'wasd'.
 *
 * Pin Connections:
 *     Port AD[7] to Photodiode Output
 *     Port B[0] to PB1
 *     Port B[1] to PB2
 *     Port T[4:2] to Select Input of the Row Decoder
 *     Port T[7:5] to Select Input of Column Decoder
 *     Port P[0] to Enable Input of the Row Decoder
 */

// Freescale libraries
#include <hidef.h>
#include <mc9s12c128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12c128"

// 348 libraries
#include "modclock.h"
#include "lcd_lib.h"

// Project libraries
#include "stdbool.h"
#include "stdint.h"
#include "bit_help.h"
#include "setup.h"
#include "snake_game.h"

/*----------------------------------------------------------------------------
 * Internal Definitions
 *----------------------------------------------------------------------------*/

// The bit positions for the row and column, inclusive
#define ROW_START       2
#define ROW_END         4
#define COLUMN_START    5
#define COLUMN_END      7

// The state of the snake game
static snake_game_t game;

// The buffers holding the next values of components of the game state
static int next_brightness;
static int next_drow;
static int next_dcol;
static bool next_paused;

// Indicates that the game needs to be restarted
static bool restart_game;

// The row and column of the LED currently being drawn
static uint8_t row;
static uint8_t col;

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

    // Initialize the buffered values to the game's initial values
    next_drow = game.drow;
    next_dcol = game.dcol;
    next_pause = game.paused;

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
    // Acknowledge the timer interrupt
    TFLG1_C7F = 0x1;

    // Select the LED at (row, col)
    PTT = set_bits(PTT, row, ROW_START, ROW_END);
    PTT = set_bits(PTT, col, COLUMN_START, COLUMN_END);

    // Drive the selected LED only if it is the snake or food
    if (game.board[row][col] == SNAKE_FOOD || game.board[row][col] > 0) {
        PWMCNT0 = 0;
        PWME0 = 0x1;
    } else {
        PWME0 = 0x0;
    }

    // Increment the row and column of the game
    col = mod(col + 1, SNAKE_ROWS);
    if (col == 0) {
        row = mod(row + 1, SNAKE_COLS);
    }

    /* If we've completed a full drawing cycle (rows has rolled over),
     * then update the game state with the new values from the buffer
     * With the updated values, move the snake. */
    if (game.row == 0) {
        game.drow = next_drow;
        game.dcol = next_dcol;
        game.paused = next_paused;

        move_snake(&game);
    }

    return;
}
