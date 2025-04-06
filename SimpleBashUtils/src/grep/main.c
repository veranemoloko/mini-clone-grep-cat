#include <pcre.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/resType.h"
#include "grep.h"
#include "options.h"
#include "parse.h"

int main(int argc, char **argv) {
  Result err = OK;
  Op configs = newConfigs();
  char *reg = NULL;
  pcre *compiledReg = NULL;

  bool isErr = ((err = parseOptions(argc, argv, &configs, &reg)) ||
                (err = regComlile(reg, &compiledReg, configs.ignoreCase)) ||
                (err = makeOutput(argc, argv, configs, compiledReg)));

  return isErr ? (printErr(err), 1) : 0;
}
