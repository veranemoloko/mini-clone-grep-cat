#include <stdbool.h>
#include <stdio.h>

#include "../common/errType.h"
#include "grep.h"
#include "options.h"
#include "parse.h"

int main(int argc, char **argv) {
  Opts configs = newConfigs();
  char *reg;

  ErrTypes err = OK;
  bool isErr = (err = parseOptions(argc, argv, &configs, &reg)) ||
               (err = makeOutput(argc, argv, reg, configs));

  return isErr ? (printErr(err), 1) : 0;
}