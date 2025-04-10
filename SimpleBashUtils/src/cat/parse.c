#include "parse.h"

#include <getopt.h>
#include <stdio.h>

#include "../common/resType.h"
#include "options.h"

const struct option longOpts[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"show-ends", no_argument, NULL, 'e'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {"show-tabs", no_argument, NULL, 't'},
                                  {0, 0, 0, 0}};

Result parseOptions(int argc, char **argv, Op *op) {
  Result res = OK;
  int encodedArg;
  while ((encodedArg = getopt_long(argc, argv, "beEnstTv", longOpts, NULL)) !=
         -1) {
    switch (encodedArg) {
      case 'b':
        op->numberNonblank = true;
        break;
      case 'e':
        op->showEnds = true;
        op->showNonprinting = true;
        break;
      case 'E':
        op->showEnds = true;
        break;
      case 'n':
        op->numberAll = true;
        break;
      case 's':
        op->squeezeBlank = true;
        break;
      case 't':
        op->showTab = true;
        op->showNonprinting = true;
        break;
      case 'T':
        op->showTab = true;
        break;
      case 'v':
        op->showNonprinting = true;
        break;
      default:
        res = INVALID_OPTIONS;
        break;
    }
  };

  if (argc <= optind) res = INVALID_FILE;

  op->endIndex = optind;

  return res;
}