################################################################################
# Configuration
################################################################################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

SRC_DIR = src
TEST_DIR = unit_tests
INC_DIR = inc

SRC_PATHS = $(SRC_DIR)/snake_game.c $(SRC_DIR)/bit_help.c \
			$(TEST_DIR)/snake_test.c

.PHONY: all clean

################################################################################
# Targets
################################################################################

all: snake_test

snake_test: $(SRC_PATHS)
	$(CC) $(CFLAGS) $^ -o snake_test -I $(INC_DIR)

clean:
	rm -f snake_test
