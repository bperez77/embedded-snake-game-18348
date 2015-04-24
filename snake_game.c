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

/*-----------------------------------------------------------------
 * Internal Definitions
 *-----------------------------------------------------------------*/

// The initial snake length
#define INIT_SNAKE_LEN        1

// Starting position of the snake head
#define INIT_HEAD_ROW (SNAKE_ROWS/2 - INIT_SNAKE_LEN/2)
#define INIT_HEAD_COL (SNAKE_COLUMNS / 2)

// The initial direction of the snake
#define INIT_DROW             0
#define INIT_DCOL            -1

// TODO: Linear congruential generator for food
// Parameters for the linear congruential PRNG
#define RAND_MULTIPLIER     129
#define RAND_OFFSET         251
#define RAND_SEED           210

/* The maximum number of times to try to randomly place food before
 * defaulting to a linear search. */
#define MAX_FOOD_TRIES       10

static int rand = RAND_SEED;

static int wrap_add(int x, int y, int limit)
static int mod(int x, int limit)
static int rand();

/*-----------------------------------------------------------------
 * Inteface Functions
 *-----------------------------------------------------------------*/

/* game_init
 *
 * Initializes the snake game. Setups up the snake on the board,
 * generates a single item of food, and sets the game as not paused.
 * Board must point to a region of memory that can hold (rows * cols)
 * bytes (sizeof(int)). Rows and cols must both be powers of 2.
 */
void game_init(snake_game_t *game, int *board, int rows, int cols)
{
    int row, col;

    // Initialize the game state
    game->paused = false;
    game->game_over = false;
    game->score = INIT_SNAKE_LEN;

    // Initialize the snake position and direction
    game->head_row = (rows/2 - INIT_SNAKE_LEN/2);
    game->head_col = cols/2;
    game->drow = INIT_DROW;
    game->dcol = INIT_DCOL;

    // Initialize the snake board, and place the snake on the board
    game->rows = rows;
    game->cols = cols;
    for (row = 0; row < rows; i++)
    {
        for (col = 0; col < cols; i++)
        {
            if ((col == game->head_col) && (game->head_row <= row) &&
                (row < game->head_row + INIT_SNAKE_LEN))
            {
                game->board[row][col] = SNAKE;
            } else {
                game->board[row][col] = EMPTY;
            }
        }
    }

    // Add a piece of food onto the board
    row = rand();
    col = rand();
    game->board[row][col] = SNAKE_FOOD;

    return;
}

void move_snake(snake_game_t *game)
{
    int next_row, next_col;
    int head_row, head_col;

    // If the game is overed or paused, then do nothing
    if (game->paused || game->game_over) {
        return;
    }

    // Get the position of where the snake's going to move
    next_row = wrap_add(game->head_row, game->drow, SNAKE_ROWS);
    next_col = wrap_add(game->head_col, game->dcol, SNAKE_COLUMNS);

    head_row = game->head_row;
    head_col = game->head_col;

    /* If the next posiition contains food, then add a piece to the
     * snake and increment the score. If another portion of the
     * snake is there, then the game is over. */
    if (game->board[next_row][next_col] == SNAKE_FOOD) {
        game->score += 1;
        game->board[next_row][next_col] = game->board[head_row][head_col] + 1;

        generate_food(&(game->board));
        return;
    } else if (board[next_row][next_col] > 0) {
        game->game_over = true;
        return;
    }

    // Otherwise, if nothing was there, then move the head of the snake
    game->board[next_row][next_col] = game->board[head_row][head_col] + 1;

    // Move the rest of the snake
    for (row = 0; row < game->rows; row++)
    {
        for (col = 0; col < game->cols; col++)
        {
            if (game->board[row][col] > 0) {
                game->board[row][col] -= 1;
            }
        }
    }

    return;
}

/*-----------------------------------------------------------------
 * Internal Functions
 *-----------------------------------------------------------------*/

/* wrap_add
 *
 * Computes the sum of x and y, with the maximum value being limit,
 * and the minimum being 0. If x+y exceeds either of these values, then
 * it wraps around as necessary.
 */
static int wrap_add(int x, int y, int limit)
{
    return (x + y) & (limit - 1);
}

/* mod
 *
 * Computes x % limit. Limit must be a power of 2. The modulo computed
 * is strictly non-negative.
 */
static int mod(int x, int limit)
{
    return x & (limit - 1);
}

static void generate_food(int *board)
{
    int i;
    int food_row, food_col;

    // Attempt to randomly generate a new position for the food
    for (i = 0; i < MAX_FOOD_TRIES; i++)
    {
        food_row = mod(rand(), snake->rows);
        food_col = mod(rand(), snake->cols);
        if (board[food_row][food_col] == SNAKE_EMPTY) {
            board[food_row][food_col] = SNAKE_FOOD;
            return;
        }
    }

    /* If the random search fails, then simply search for the first
     * empty spot on the board. */
    for (row = 0; i < game->rows; i++)
    {
        for (col = 0; col < game->cols; i++)
        {
            if (board[food_row][food_col] == SNAKE_EMPTY) {
                board[food_row][food_col] = SNAKE_FOOD;
                return;
            }
        }
    }

    return;
}

static int rand()
{
    rand = RAND_MULTIPLIER*rand + RAND_OFFSET
    return 0;
}


