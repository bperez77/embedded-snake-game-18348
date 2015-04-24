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

#include "stdbool.h"

/* The size of the game board in rows and columns. Each dimension
 * must be a power of 2, or food generation will not work properly. */
#define SNAKE_ROWS        8
#define SNAKE_COLUMNS     8

/* Food is represented by -1, an empty spot by 0, and any part of
 * the snake is represented by a positive integer. The head is the
 * highest number. */
#define SNAKE_FOOD         -1
#define SNAKE_EMPTY         0

// The state of the snake game
typedef struct {
    bool paused;
    bool game_over;
    int score;

    int head_row;
    int head_col;
    int drow;
    int dcol;

    int board[SNAKE_ROWS][SNAKE_COLUMNS];
} snake_game_t;

#endif /* SNAKE_GAME_H_ */
