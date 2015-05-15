################################################################################
# Configuration
################################################################################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

DOC_CC = pdflatex
DOC_FLAGS = -shell-escape -synctex=1 -interaction=nonstopmode \
		    -output-directory ../

SRC_DIR = src
TEST_DIR = unit_tests
INC_DIR = inc
DOC_DIR = doc

SRC_PATHS = $(SRC_DIR)/snake_game.c $(SRC_DIR)/bit_help.c \
			$(TEST_DIR)/snake_test.c

DOC_PATHS = $(DOC_DIR)/design.tex
REPORT_PATHS = $(DOC_DIR)/report.tex

.PHONY: all clean veryclean

################################################################################
# Targets
################################################################################

all: snake_test

snake_test: $(SRC_PATHS)
	$(CC) $(CFLAGS) $^ -o snake_test -I $(INC_DIR)

design: $(DOC_PATHS)
	cd $(DOC_DIR) && \
	$(DOC_CC) $(DOC_FLAGS) $^

report: $(REPORT_PATHS)
	cd $(DOC_DIR) && \
	$(DOC_CC) $(DOC_FLAGS) $^

clean:
	rm -f snake_test *.aux *.ps *.pyg *.synctex.gz *.dvi *.log

veryclean: clean
	rm -f report.pdf design.pdf
