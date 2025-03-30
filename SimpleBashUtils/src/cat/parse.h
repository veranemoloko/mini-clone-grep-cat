#ifndef READ_ARGS_H
#define READ_ARGS_H

#include "../common/errType.h"
#include "options.h"

ErrTypes parseOptions(int, char **, Opts *);

#endif