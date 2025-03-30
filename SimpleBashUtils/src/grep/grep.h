#ifndef GREP_H
#define GREP_H

#include "../common/errType.h"
#include "options.h"

ErrTypes makeOutput(int, char **, char *, Opts);

#endif