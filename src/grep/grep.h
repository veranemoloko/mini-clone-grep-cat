#ifndef GREP_H
#define GREP_H

#include <pcre.h>

#include "../common/resType.h"
#include "options.h"

Result regCompile(char *, pcre **, bool);
Result makeOutput(int, char **, Op, pcre *);

#endif