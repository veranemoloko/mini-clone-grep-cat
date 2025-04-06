#include <stdbool.h>

#include "../common/errType.h"
#include "cat.h"
#include "options.h"
#include "parse.h"

int main(int argc, char **argv) {

  Opts configs = newConfigs();

  Result err = OK;
  bool isErr = (err = parseOptions(argc, argv, &configs)) ||
               (err = makeOutput(argc, argv, configs));

  return isErr ? (printErr(err), 1) : 0;
}