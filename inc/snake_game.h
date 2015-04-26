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
 *
 * This file contains the interface to the snake game module, the definition
 * of the structure that represents the state of the game, and constants
 * defining the pieces on the board and the size of the board.
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
    bool paused;        // Indicates if the game is paused
    bool game_over;     // Indicates if the game has ended
    int score;          // The score of the game

    int head_row;       // The row at which the head of the snake is
    int head_col;       // The column at which the head of the snake is
    int drow;           // The x direction of the snake
    int dcol;           // The y direction of the snake

    int board[SNAKE_ROWS][SNAKE_COLUMNS];   // The game board
} snake_game_t;

/* game_init
 *
 * Initializes the snake game. Setups up the snake on the board,
 * generates a single item of food, and sets the game as paused.
 */
void game_init(snake_game_t *game);

/* move_snake
 *
 * Moves the snake exactly one place, updating the board appropiately.
 * The movement of the snake permits it to wrap around the board. If
 * the head of the snakes moves into food, then it "eats" it, which
 * causes its size to grow by one. If the snake intersects with itself,
 * then the game ends.
 */
void move_snake(snake_game_t *game);

#endif /* SNAKE_GAME_H_ */
