#ifndef RESTYPE_H
#define RESTYPE_H

typedef enum { OK, MEM_ERR, INVALID_FILE, INVALID_OPTIONS, INVALID_REG, USAGE } Result;

void printErr(Result);

#endif