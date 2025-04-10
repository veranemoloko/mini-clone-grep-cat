#include "resType.h"

#include <stdio.h>

void printErr(Result res) {
  switch (res) {
  case USAGE:
    printf("Usage: grep [OPTION]... PATTERNS [FILE]...");
    break;
  case INVALID_OPTIONS:
    printf("Error: The options is invalid.\n");
    break;
  case MEM_ERR:
    printf("Error: Memory.\n");
    break;
  case INVALID_FILE:
  case INVALID_REG:
    break;
  case OK:
    break;
  }
}