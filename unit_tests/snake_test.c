#include <stdio.h>
#include <assert.h>

#include "snake_game.h"

snake_game_t game;

void remove_food(snake_game_t *game)
{
    int row, col;

    for (row = 0; row < SNAKE_ROWS; row++)
    {
        for (col = 0; col < SNAKE_COLUMNS; col++)
        {
            if (game->board[row][col] == SNAKE_FOOD) {
                game->board[row][col] = SNAKE_EMPTY;
            }
        }
    }

    return;
}

void test_init()
{
    int row, col;
    bool food_found;

    snake_init(&game);

    assert(game.paused);
    assert(!game.game_over);
    assert(game.score == 1);
    assert(game.head_row == 4);
    assert(game.head_col == 4);
    assert(game.drow == 0);
    assert(game.dcol == -1);

    assert(game.board[game.head_row][game.head_col] == 1);

    // Check that exactly one piece of food exists on the board
    food_found = false;
    for (row = 0; row < SNAKE_ROWS; row++)
    {
        for (col = 0; col < SNAKE_COLUMNS; col++)
        {
            if (game.board[row][col] == SNAKE_FOOD) {
                assert(!food_found);
                food_found = true;
            } else if (row != game.head_row && col != game.head_col) {
                assert(game.board[row][col] == SNAKE_EMPTY);
            }
        }
    }
    assert(food_found);

    printf("Initialization Tests Passed!\n");
    return;
}

void test_move()
{
    snake_init(&game);

    // When the game is paused, no movement should happend
    move_snake(&game);
    assert(game.head_row == 4);
    assert(game.head_col == 4);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Move left
    game.paused = false;
    move_snake(&game);
    assert(game.head_row == 4);
    assert(game.head_col == 3);
    assert(game.board[4][4] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Move up
    game.drow = -1;
    game.dcol = 0;
    move_snake(&game);
    assert(game.head_row == 3);
    assert(game.head_col == 3);
    assert(game.board[4][3] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Move right
    game.drow = 0;
    game.dcol = 1;
    move_snake(&game);
    assert(game.head_row == 3);
    assert(game.head_col == 4);
    assert(game.board[3][3] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Move down
    game.drow = 1;
    game.dcol = 0;
    move_snake(&game);
    assert(game.head_row == 4);
    assert(game.head_col == 4);
    assert(game.board[3][4] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Test wrap-around (moving left)
    game.drow = 0;
    game.dcol = -1;
    move_snake(&game);
    move_snake(&game);
    move_snake(&game);
    move_snake(&game);
    move_snake(&game);
    assert(game.head_row == 4);
    assert(game.head_col == 7);
    assert(game.board[4][4] == SNAKE_EMPTY);
    assert(game.board[4][3] == SNAKE_EMPTY);
    assert(game.board[4][2] == SNAKE_EMPTY);
    assert(game.board[4][1] == SNAKE_EMPTY);
    assert(game.board[4][0] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Test wrap-around (moving right)
    game.drow = 0;
    game.dcol = 1;
    move_snake(&game);
    assert(game.head_row == 4);
    assert(game.head_col == 0);
    assert(game.board[4][7] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Test wrap-around (moving down)
    game.drow = 1;
    game.dcol = 0;
    move_snake(&game);
    move_snake(&game);
    move_snake(&game);
    move_snake(&game);
    assert(game.head_row == 0);
    assert(game.head_col == 0);
    assert(game.board[4][0] == SNAKE_EMPTY);
    assert(game.board[5][0] == SNAKE_EMPTY);
    assert(game.board[6][0] == SNAKE_EMPTY);
    assert(game.board[7][0] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    // Test wrap-around (moving up)
    game.drow = -1;
    game.dcol = 0;
    move_snake(&game);
    assert(game.head_row == 7);
    assert(game.head_col == 0);
    assert(game.board[0][0] == SNAKE_EMPTY);
    assert(game.board[game.head_row][game.head_col] == 1);

    printf("Movement Tests Passed!\n");
    return;
}

void test_food()
{
    int row, col;
    bool food_found;

    snake_init(&game);
    game.paused = false;

    // Put the food right in front of the snake, remove the other
    remove_food(&game);
    game.board[game.head_row+game.drow][game.head_col+game.dcol] = SNAKE_FOOD;

    // Test that the snake grows properly
    move_snake(&game);
    assert(game.head_row == 4);
    assert(game.head_col == 3);
    assert(game.board[4][4] == 1);
    assert(game.board[game.head_row][game.head_col] == 2);
    assert(game.score == 2);

    // Check that a new piece of food was properly generated
    food_found = false;
    for (row = 0; row < SNAKE_ROWS; row++)
    {
        for (col = 0; col < SNAKE_COLUMNS; col++)
        {
            if (game.board[row][col] == SNAKE_FOOD) {
                assert(!food_found);
                food_found = true;
            } else if (row != game.head_row && row != (game.head_row-game.drow)
                    && col != game.head_col && col != (game.head_col-game.dcol))
            {
                assert(game.board[row][col] == SNAKE_EMPTY);
            }
        }
    }
    assert(food_found);

    printf("Food Tests Passed!\n");
    return;
}

void test_gameover()
{
    snake_init(&game);
    game.paused = false;

    // Grow the size of the snake
    remove_food(&game);
    game.board[game.head_row+game.drow][game.head_col+game.dcol] = SNAKE_FOOD;
    move_snake(&game);
    assert(game.score == 2);

    remove_food(&game);
    game.board[game.head_row+game.drow][game.head_col+game.dcol] = SNAKE_FOOD;
    move_snake(&game);
    assert(game.score == 3);

    remove_food(&game);
    game.board[game.head_row+game.drow][game.head_col+game.dcol] = SNAKE_FOOD;
    move_snake(&game);
    assert(game.score == 4);

    remove_food(&game);
    game.board[game.head_row+game.drow][game.head_col+game.dcol] = SNAKE_FOOD;
    move_snake(&game);
    assert(game.score == 5);

    // Intersect the snake with itself
    game.drow = -1;
    game.dcol = 0;
    move_snake(&game);

    game.drow = 0;
    game.dcol = 1;
    move_snake(&game);

    game.drow = 1;
    game.dcol = 0;
    move_snake(&game);

    assert(game.game_over);
    assert(game.head_row == 3);
    assert(game.head_col == 1);
    assert(game.score == 5);

    // Try moving the snake after the game is over
    move_snake(&game);
    assert(game.game_over);
    assert(game.head_row == 3);
    assert(game.head_col == 1);
    assert(game.score == 5);

    printf("Game Over Tests Passed!\n");
    return;
}

int main()
{
    test_init();
    test_move();
    test_food();
    test_gameover();

    printf("All Tests Passed!\n");
    return 0;
}
