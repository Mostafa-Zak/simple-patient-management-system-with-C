
# Makefile for PMS project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN = $(OBJ_DIR)/pms

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(BIN)

# Link objects into the final binary
$(BIN): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -lsqlite3 -o $@

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: all
	$(BIN)

# Clean build files
clean:
	rm -rf $(OBJ_DIR)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild run
