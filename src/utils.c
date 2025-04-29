#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *userInput() {
  char *input = malloc(50);
  fgets(input, 50, stdin);
  input[strcspn(input, "\n")] = 0; // remove newline
  return input;
};

char *getInput(const char *prompt) {
  printf("%s", prompt); // Show user what to do
  return userInput();   // Get their input and return it
}
