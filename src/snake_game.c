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
 * This is the module that manages the snake game. The game is represented
 * by a 2D array, corresponding to the LED array that it is mapped onto.
 * Food is represented by -1, and empty spot by 0, and a positive integer
 * represents a part of the snake. The head of the snake is the largest
 * number, and it monotonically decreases to the tail.
 *
 * The game commences as long as the snake does not intersect with
 * itself, at which point, the game ends. Whenever the snake eats food,
 * it grows in size by 1, and the user's score increases by 1.
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

// Parameters for the linear congruential PRNG
#define RAND_MULTIPLIER     129
#define RAND_OFFSET         251
#define RAND_SEED           210

/* The maximum number of times to try to randomly place food before
 * defaulting to a linear search. */
#define MAX_FOOD_TRIES       10

static int seed = RAND_SEED;

static void generate_food(int board[SNAKE_ROWS][SNAKE_COLUMNS]);
static int wrap_add(int x, int y, int limit);
static int mod(int x, int limit);
static int rand();

/*-----------------------------------------------------------------
 * Inteface Functions
 *-----------------------------------------------------------------*/

/* snake_init
 *
 * Initializes the snake game. Setups up the snake on the board,
 * generates a single item of food, and sets the game as paused.
 */
void snake_init(snake_game_t *game)
{
    int row, col;

    // Initialize the game state
    game->paused = true;
    game->game_over = false;
    game->score = INIT_SNAKE_LEN;

    // Initialize the snake position and direction
    game->head_row = INIT_HEAD_ROW / 2;
    game->head_col = INIT_HEAD_COL/2 - INIT_SNAKE_LEN/2;
    game->drow = INIT_DROW;
    game->dcol = INIT_DCOL;

    // Initialize the snake board, and place the snake on the board
    for (row = 0; row < SNAKE_ROWS; row++)
    {
        for (col = 0; col < SNAKE_COLUMNS; col++)
        {
            if ((row == INIT_HEAD_ROW) && (INIT_HEAD_COL <= col) &&
                (col < INIT_HEAD_COL + INIT_SNAKE_LEN))
            {
                game->board[row][col] = INIT_SNAKE_LEN - (col - INIT_HEAD_COL);
            } else {
                game->board[row][col] = SNAKE_EMPTY;
            }
        }
    }

    // Add a piece of food onto the board
    generate_food(game->board);

    return;
}

/* move_snake
 *
 * Moves the snake exactly one place, updating the board appropiately.
 * The movement of the snake permits it to wrap around the board. If
 * the head of the snakes moves into food, then it "eats" it, which
 * causes its size to grow by one. If the snake intersects with itself,
 * then the game ends.
 */
void move_snake(snake_game_t *game)
{
    int row, col;
    int next_row, next_col;
    int head_row, head_col;

    // If the game is overed or paused, then do nothing
    if (game->paused || game->game_over) {
        return;
    }

    // Get the position of where the snake's going to move
    next_row = mod(game->head_row + game->drow, SNAKE_ROWS);
    next_col = mod(game->head_col + game->dcol, SNAKE_COLUMNS);

    head_row = game->head_row;
    head_col = game->head_col;

    /* If the next posiition contains food, then add a piece to the
     * snake and increment the score. If another portion of the
     * snake is there, then the game is over. */
    if (game->board[next_row][next_col] == SNAKE_FOOD) {
        game->score += 1;
        game->board[next_row][next_col] = game->board[head_row][head_col] + 1;

        generate_food(game->board);
        return;
    } else if (game->board[next_row][next_col] > 0) {
        game->game_over = true;
        return;
    }

    // Otherwise, if nothing was there, then move the head of the snake
    game->board[next_row][next_col] = game->board[head_row][head_col] + 1;

    // Move the rest of the snake
    for (row = 0; row < SNAKE_ROWS; row++)
    {
        for (col = 0; col < SNAKE_COLUMNS; col++)
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

/* generate_food
 *
 * Generates a new piece of food, and places it randomly on the board.
 * This occurs after a snake eats a piece of food. This functions
 * attempts to place the food randomly MAX_FOOD_TRIES times. If
 * every time leads to a conflict, then it gives up and searches the
 * board for the first empty location, and places the food there.
 */
static void generate_food(int board[SNAKE_ROWS][SNAKE_COLUMNS])
{
    int i;
    int row, col;
    int food_row, food_col;

    // Attempt to randomly generate a new position for the food
    for (i = 0; i < MAX_FOOD_TRIES; i++)
    {
        food_row = mod(rand(), SNAKE_ROWS);
        food_col = mod(rand(), SNAKE_COLUMNS);
        if (board[food_row][food_col] == SNAKE_EMPTY) {
            board[food_row][food_col] = SNAKE_FOOD;
            return;
        }
    }

    /* If the random search fails, then simply search for the first
     * empty spot on the board. */
    for (row = 0; i < SNAKE_ROWS; row++)
    {
        for (col = 0; col < SNAKE_COLUMNS; col++)
        {
            if (board[food_row][food_col] == SNAKE_EMPTY) {
                board[food_row][food_col] = SNAKE_FOOD;
                return;
            }
        }
    }

    return;
}


/* rand
 *
 * This function is a simple 16-bit linear congruential pseudo-random
 * number generator. This function is not reentrant.
 */
static int rand()
{
    seed = RAND_MULTIPLIER*seed + RAND_OFFSET;
    return seed;
}
