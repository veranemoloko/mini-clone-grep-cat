#include "cat.h"
#define _GNU_SOURCE
#include "../common/errType.h"
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_END '$'
#define PRINT_TAB "^I"

void showTab(char *buffer, bool status) {
  size_t j = 0;
  while (buffer[j] != '\0') {
    if (status && buffer[j] == '\t') {
      printf("%s", PRINT_TAB);
    } else if (buffer[j] != '\n') {
      printf("%c", buffer[j]);
    }
    j++;
  }
}

Result makeOutput(const int argc, char **argv, const Opts opts) {
  Result err = OK;
  int strCnt = 1;
  int emptyStrCnt = 0;

  for (int i = 0; i < argc - opts.endIndex; i++) {
    FILE *file = fopen(argv[opts.endIndex + i], "r");
    if (file == NULL)
      return INVALID_FILE;

    char *buffer = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&buffer, &len, file)) != -1) {

      emptyStrCnt = (strlen(buffer) <= 1) ? emptyStrCnt + 1 : 0;
      if (opts.squeezeBlank && emptyStrCnt >= 2)
        continue;

      bool newLine = buffer[(strlen(buffer)) - 1] == '\n' ? true : false;

      if (opts.numberNonblank && !emptyStrCnt)
        printf("%5d  ", strCnt++);
      else if (opts.numberAll && (!opts.numberNonblank))
        printf("%5d  ", strCnt++);

      showTab(buffer, opts.showTab);

      if (opts.showEnds)
        printf("%c", PRINT_END);

      if (newLine)
        printf("\n");
    }
    free(buffer);
    fclose(file);
  }
  return err;
}
