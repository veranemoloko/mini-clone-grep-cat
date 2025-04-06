#ifndef GREP_H
#define GREP_H

#include "../common/errType.h"
#include "options.h"
#include <pcre.h>

Result regComlile(char *, pcre **, bool);
Result makeOutput(int, char **, Opts, pcre *);

#endif