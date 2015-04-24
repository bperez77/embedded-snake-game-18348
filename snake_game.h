/* snake_game.h
 *
 * ECE348, Spring 2015
 * Group C4
 * Brandon Perez bmperez
 * Rohit Banerjee rohitban
 *
 * Target: MC9S12C128
 * CodeWarrior Version: 5.1
 *
 * Created: Fri 24 Apr 2015 03:55:24 PM EDT
 * Last Modified: TODO: Update
 */

#ifndef SNAKE_GAME_H_
#define SNAKE_GAME_H_

#include <stdbool.h>

/* The size of the game board in rows and columns. Each dimension
 * must be a power of 2, or food generation will not work properly. */
#define SNAKE_ROWS        8
#define SNAKE_COLUMNS     8

// The types of items that can be on the board
typedef enum {
    EMPTY   = 0,
    SNAKE   = 1,
    FOOD    = -1,
} board_elem_t;

// The state of the snake game
typedef struct {
    bool paused;
    bool game_over;
    int head_row;
    int head_col;
    int drow;
    int dcol;
    int score;
    board_elem_t board[ROWS][COLUMNS];
} snake_game_t;

#endif /* SNAKE_GAME_H_
