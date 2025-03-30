#include "parse.h"
#include "../common/errType.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>

ErrTypes parseOptions(int argc, char **argv, Opts *op) {
  ErrTypes err = OK;

  if (argc == 1)
    err = INVALID_FILE;

  const struct option longOpts[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                    {"show-ends", no_argument, NULL, 'e'},
                                    {"number", no_argument, NULL, 'n'},
                                    {"squeeze-blank", no_argument, NULL, 's'},
                                    {"show-tabs", no_argument, NULL, 't'},
                                    {0, 0, 0, 0}};

  int res;
  while ((res = getopt_long(argc, argv, "beEnstTv", longOpts, NULL)) != -1) {
    switch (res) {
    case 'b':
      op->numberNonblank = true;
      break;
    case 'e':
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
    case 'T':
      op->showTab = true;
      break;
    case 'v':
      op->showNonprinting = true;
      break;
    default:
      err = INVALID_OPTIONS;
    }
  };

  if (argc <= optind)
    err = INVALID_FILE;

  op->endIndex = optind;
  return err;
}