#!/usr/bin/env bash

gcc -Wall -Wextra -o ./build/intern \
  ./src/main.c ./src/ds.c \
  -I./external \
  -L./external -lsqlite3 \
  -Wl,-rpath=./external \
  -lraylib -lm -ldl -lpthread
