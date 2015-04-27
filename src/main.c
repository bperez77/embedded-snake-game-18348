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
 * Externally Visible Items:
 *     void main()   
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
#include <stdio.h>
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
#define ROW_START        2
#define ROW_END          4
#define COLUMN_START     5
#define COLUMN_END       7

// The size of the buffer to store strings
#define BUFSIZE         20

// The state of the snake game
static snake_game_t game;

// Indicates that the game needs to be restarted
static bool restart_game;

// The measured brightness from the photodiode
static volatile uint8_t brightness;

// The row and column of the LED currently being drawn
static uint8_t row;
static uint8_t col;

/*----------------------------------------------------------------------------
 * Main Routine
 *----------------------------------------------------------------------------*/

/* main
 *
 * The main routine.
 *
 * The main routine runs all of the setup an initialization code, then runs in
 * a loop forever. In the loop, it reads the paused and restart game buttons,
 * and update the state appropiately. Also, it displays the current score on the
 * LCD screen, along with the A/D input value.
 */
void main()
{
    char score_buf[BUFSIZE];
    char atd_buf[BUFSIZE];

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
    row = 0;
    col = 0;
    restart_game = false;
    brightness = PWM_INIT_DUTY;
    snake_init(&game);

    // Enable all interrupts
    EnableInterrupts;

    // TODO: Maybe software debouncing is needed?
    /* Loop forever, reading the user input, and updating the game
     * state appropiately. */
    for (;;)
    {
        // Check if the pause button was pressed, and toggle the pause
        if (!PORTB_BIT0) {
            game.paused = !game.paused;
        }

        // Check if the reset button was pressed
        if (!PORTB_BIT1) {
            restart_game = true;
        }

        // Format the strings for the score and brightness
        (void)sprintf(score_buf, "Score: %d", game.score);
        (void)sprintf(atd_buf, "Brightness: 0x%02x", brightness);

        // Display the score and brightness A/D conversion to the LED's
        lcdWriteLine(1, score_buf);
        lcdWriteLine(2, atd_buf);
    }
}

/*----------------------------------------------------------------------------
 * Interrupts
 *----------------------------------------------------------------------------*/

/* sci_interrupt
 *
 * This function handles interrupts from the onboard SCI (serial) module,
 * specifically whenever a new data byte is received. This function reads the
 * byte as a character, then updates the snake direction appropiately. 'w'
 * is up, 'a' is left, 's' is down, and 'd' is right.
 */
void interrupt VectorNumber_Vsci sci_interrupt()
{
    uint8_t received_char;

    // Acknowledge serial interrupt and read the character sent
    if (!SCISR1_RDRF) {
        return;
    }
    received_char = SCIBDL;

    /* Update the snake direction based on the received input. 'w' is up,
     * 'a' is left, 's' is down, 'd' is right. */
    switch (received_char)
    {
        case 'w':
            game.drow = 0;
            game.dcol = -1;
            break;
        case 'a':
            game.drow = -1;
            game.dcol = 0;
            break;
        case 's':
            game.drow = 0;
            game.dcol = 1;
            break;
        case 'd':
            game.drow = 1;
            game.dcol = 0;
            break;
    }

    return;
}

/* atd_interrupt
 *
 * This function handles interrupts from the A/D converter module, which
 * occurs whenever a new conversion is ready. This function simply reads
 * the conversion as the ambient brightness, then updates the duty cycle
 * of the PWM to counteract this brightness.
 */
void interrupt VectorNumber_Vatd0 atd_interrupt()
{
    // Ackowledge the ATD interrupt
    ATDSTAT0_SCF = 0x1;

    // Read out new brightness value, and update the duty cycle
    brightness = ATDDR0H;
    PWMDTY0 = PWM_PERIOD - brightness;

    return;
}

/* tc7_interrupt
 *
 * This function handles interrupts from the Timer module, which occurs
 * whenever the timer counter value is equal to the comparison value on
 * channel 7 (every 15 ms). This function draws the next LED on the board,
 * and adjusts the PWM appropiately. If a complete drawing cycle is complete,
 * then this function either moves the snake, or resets the game, if the user
 * pressed the reset game button.
 */
void interrupt VectorNumber_Vtimch7 tc7_interrupt()
{
    // Acknowledge the timer interrupt
    TFLG1_C7F = 0x1;

    // Select the LED at (row, col). Match the assertion level for each
    PTT = set_bits(PTT, ~row, ROW_START, ROW_END);
    PTT = set_bits(PTT, col, COLUMN_START, COLUMN_END);

    // Drive the selected LED only if it is the snake or food
    if (game.board[row][col] == SNAKE_FOOD || game.board[row][col] > 0) {
        PWMCNT0 = 0;
        PWME_PWME0 = 0x1;
    } else {
        PWME_PWME0 = 0x0;
    }

    // Increment the row and column of the game
    col = mod_8(col + 1, SNAKE_ROWS);
    if (col == 0) {
        row = mod_8(row + 1, SNAKE_COLUMNS);
    }

    /* If we've completed a full drawing cycle (rows has rolled over),
     * then check if the user requested a reset. If so, reset the game,
     * otherwise, move the snake. */
    if (row == 0 && restart_game) {
        snake_init(&game);
        restart_game = false;
    } else if (row == 0) {
        move_snake(&game);
    }

    return;
}
