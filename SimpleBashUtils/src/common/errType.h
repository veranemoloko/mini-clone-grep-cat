#ifndef ERRTYPE_H
#define ERRTYPE_H

typedef enum {
  OK,
  MEM_ERR,
  INVALID_FILE,
  INVALID_OPTIONS,
  INVALID_REG,
} ErrTypes;

void printErr(ErrTypes);

#endif