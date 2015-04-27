################################################################################
# Configuration
################################################################################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

DOC_CC = pdflatex
DOC_FLAGS = -shell-escape -synctex=1 -interaction=nonstopmode

SRC_DIR = src
TEST_DIR = unit_tests
INC_DIR = inc

SRC_PATHS = $(SRC_DIR)/snake_game.c $(SRC_DIR)/bit_help.c \
			$(TEST_DIR)/snake_test.c

DOC_PATHS = design.tex

REPORT_PATHS = report.tex

.PHONY: all clean

################################################################################
# Targets
################################################################################

all: snake_test

snake_test: $(SRC_PATHS)
	$(CC) $(CFLAGS) $^ -o snake_test -I $(INC_DIR)

design_doc: $(DOC_PATHS)
	$(DOC_CC) $(DOC_FLAGS) $^

report: $(REPORT_PATHS)
	$(DOC_CC) $(DOC_FLAGS) $^

clean:
	rm -f snake_test *.aux *.ps *.pyg *.synctex.gz *.dvi *.log
