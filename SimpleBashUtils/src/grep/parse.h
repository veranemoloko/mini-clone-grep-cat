#ifndef PARSE_H
#define PARSE_H

#include "../common/errType.h"
#include "options.h"

ErrTypes parseOptions(int, char **, Opts *, char **);

#endif