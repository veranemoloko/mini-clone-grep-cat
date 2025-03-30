#include "parse.h"
#include "../common/errType.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>

ErrTypes parseOptions(int argc, char **argv, Opts *op, char **reg) {
  ErrTypes err = OK;

  if (argc == 1)
    err = INVALID_FILE;

  const struct option longOpts[] = {
      {"regexp", required_argument, NULL, 'e'},
      {"ignore-case", no_argument, NULL, 'i'},
      {"invert-match", no_argument, NULL, 'v'},
      {"count", no_argument, NULL, 'c'},
      {"files-with-matches", no_argument, NULL, 'l'},
      {"line-number", no_argument, NULL, 'n'},
      {0, 0, 0, 0}};

  int res;
  while ((res = getopt_long(argc, argv, "e:ivcln", longOpts, NULL)) != -1) {
    switch (res) {
    case 'e':
      op->pattern = true;
      (*reg) = optarg;
      break;
    case 'i':
      op->ignoreCase = true;
      break;
    case 'v':
      op->invertMatch = true;
      break;
    case 'c':
      op->countMatch = true;
      break;
    case 'l':
      op->filesMatch = true;
      break;
    case 'n':
      op->lineNumber = true;
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