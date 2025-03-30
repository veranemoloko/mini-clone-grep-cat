#include "grep.h"
#define _GNU_SOURCE
#include "../common/errType.h"
#include "options.h"
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printGrep(int match, char *buffer, Opts opts, int *cntMatch, int cntStr) {
  if ((match >= 0 && !opts.invertMatch) || (match < 0 && opts.invertMatch)) {
    (*cntMatch)++;
    if (!opts.countMatch && !opts.filesMatch) {
      if (opts.lineNumber) {
        printf("%d:%s", cntStr, buffer);
      } else {
        printf("%s", buffer);
      }
    }
  }
}

ErrTypes makeOutput(int argc, char **argv, char *reg, Opts opts) {
  ErrTypes err = OK;
  int erroffset;
  const char *error;
  int prce_op = opts.ignoreCase ? PCRE_CASELESS : 0;
  pcre *resReg = pcre_compile(reg, prce_op, &error, &erroffset, NULL);
  if (!resReg) {
    printf("Error: %s\nIndex error: %d\n", error, erroffset);
    return INVALID_REG;
  }

  int cntMatch = 0, cntStr = 0;
  for (int i = 0; i < argc - opts.endIndex; i++) {
    FILE *file = fopen(argv[opts.endIndex + i], "r");
    if (file == NULL)
      return INVALID_FILE;

    char *buffer = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&buffer, &len, file)) != -1) {
      int ovector[30];
      int match = pcre_exec(resReg, NULL, buffer, len, 0, 0, ovector, 30);
      if (opts.filesMatch && cntMatch > 0) {
        printf("%s", argv[opts.endIndex + i]);
        break;
      }

      cntStr++;
      printGrep(match, buffer, opts, &cntMatch, cntStr);
    }

    if (opts.countMatch)
      printf("%d", cntMatch);

    free(buffer);
    fclose(file);
  }
  return err;
}