#ifndef ERRTYPE_H
#define ERRTYPE_H

typedef enum {
  OK,
  INVALID_FILE,
  INVALID_OPTIONS,
  INVALID_REG,
} ErrTypes;

void printErr(ErrTypes);

#endif