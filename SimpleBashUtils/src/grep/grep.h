#ifndef GREP_H
#define GREP_H

#include "../common/resType.h"
#include "options.h"
#include <pcre.h>

Result regComlile(char *, pcre **, bool);
Result makeOutput(int, char **, Op, pcre *);

#endif