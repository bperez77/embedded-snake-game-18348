/* snake_game.c
 *
 * ECE348, Spring 2015
 * Group C4
 * Brandon Perez bmperez
 * Rohit Banerjee rohitban
 *
 * Target: MC9S12C128
 * CodeWarrior Version: 5.1
 *
 * Created: Fri 24 Apr 2015 03:55:00 PM EDT
 * Last Modified: TODO: Update
 *
 * TODO: ENTER PROGRAM NAME HERE
 *
 * TODO: ENTER PROGRAM DESCRIPTION HERE
 *
 * Externally Visible Items:
 *     void init_game(snake_game_t *game)
 *     void move_snake(snake_game_t *game)
 */

#include "snake_game.h"

// The initial snake length
#define INIT_SNAKE_LEN   1

// Starting position of the snake head
#define INIT_HEAD_ROW (SNAKE_ROWS/2 - INIT_SNAKE_LEN/2)
#define INIT_HEAD_COL (SNAKE_COLUMNS / 2)

// The initial direction of the snake
#define INIT_DROW        0
#define INIT_DCOL       -1

// TODO: Linear congruential generator for food
// Parameters for the linear congruential PRNG
#define INIT_FOOD_ROW    0
#define INIT_FOOD_COL    0

/*-----------------------------------------------------------------
 * Inteface Functions
 *-----------------------------------------------------------------*/

/* game_init
 *
 * Initializes the snake game. Setups up the snake on the board,
 * generates a single item of food, and sets the game as not paused.
 */
void game_init(snake_game_t *game)
{
    int row, col;

    // Initialize the game state
    game->paused = false;
    game->game_over = false;
    game->score = INIT_SNAKE_LEN;

    // Initialize the snake position and direction
    game->head_row = INIT_HEAD_ROW;
    game->head_col = INIT_HEAD_COL;
    game->drow = INIT_DROW;
    game->dcol = INIT_DCOL;

    // Initialize the snake board, and place the snake on the board
    for (row = 0; row < SNAKE_ROWS; i++)
    {
        for (col = 0; col < SNAKE_COLUMNS; i++)
        {
            if ((col == INIT_HEAD_COL) && (INIT_HEAD_ROW <= row) &&
                (row < INIT_HEAD_ROW + INIT_SNAKE_LEN))
            {
                game->board[row][col] = SNAKE;
            } else {
                game->board[row][col] = EMPTY;
            }
        }
    }

    // Add a piece of food onto the board
    game->board[INIT_FOOD_ROW][INIT_FOOD_COL] = FOOD;

    return;
}

void move_snake(snake_game_t *game)
{
    return;
}

/*-----------------------------------------------------------------
 * Internal Functions
 *-----------------------------------------------------------------*/

// TODO: Implement linear congruential generator
int rand()
{
    return 0;
}


