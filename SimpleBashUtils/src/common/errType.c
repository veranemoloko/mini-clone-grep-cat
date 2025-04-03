#include "errType.h"

#include <stdio.h>

void printErr(ErrTypes errEnum) {
  switch (errEnum) {
  case INVALID_FILE:
    printf("Error: The files is invalid.\n");
    break;
  case INVALID_OPTIONS:
    printf("Error: The options is invalid.\n");
    break;
  case INVALID_REG:
  case MEM_ERR:
    break;
  case OK:
    break;
  }
}