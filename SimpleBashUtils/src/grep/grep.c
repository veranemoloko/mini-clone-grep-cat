#define _GNU_SOURCE
#include "grep.h"
#include "../common/errType.h"
#include "options.h"
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Result regComlile(char *reg, pcre **compiledReg, bool ignoreCase) {
  Result res = OK;
  int erroffset;
  const char *error;
  int prce_op = ignoreCase ? PCRE_CASELESS : 0;
  *compiledReg = pcre_compile(reg, prce_op, &error, &erroffset, NULL);
  if (*compiledReg == NULL) {
    printf("Error: %s\nIndex error: %d\n", error, erroffset);
    res = INVALID_REG;
  }
  free(reg);
  reg = NULL;
  return res;
}

void printStr(int matches, char *buffer, Opts op, int *cntMatch, int cntStr) {
  if (((matches >= 0) && !op.invertMatch) ||
      ((matches < 0) && op.invertMatch)) {
    (*cntMatch)++;
    if (!op.countMatch && !op.filesMatch) {
      if (op.lineNumber) {
        printf("%d:%s", cntStr, buffer);
      } else {
        printf("%s", buffer);
      }
    }
  }
}

void printCntMatch(Opts op, int cntMatch, int cntFiles, char *fileName) {
  if (cntFiles > 1 && op.countMatch && !op.noFileName)
    printf("%s:", fileName);
  if (op.countMatch)
    printf("%d\n", cntMatch);
}

bool printFileName(Opts op, int matches, int cntFiles, char *fileName) {
  bool isBreak = false;
  if ((op.filesMatch && matches > 0 && !op.invertMatch) ||
      (op.filesMatch && matches < 1 && op.invertMatch)) {
    printf("%s\n", fileName);
    isBreak = true;
  } else if (matches > 0 && cntFiles > 1 && !op.filesMatch && !op.countMatch &&
             !op.noFileName) {
    printf("%s:", fileName);
  }
  return isBreak;
}

char *makeStr(int matches, int *ovector, char *buffer) {
  size_t len = strlen(buffer);
  char *newStr = malloc(len + 2);
  if (newStr != NULL) {
    int newSize = 0;
    for (int i = 0; i < matches; i++) {
      for (int j = ovector[i * 2]; j < ovector[(i * 2) + 1]; j++) {
        newStr[newSize++] = buffer[j];
      }
    }
    newStr[newSize] = '\n';
    newStr[newSize + 1] = '\0';
  }
  return newStr;
}

Result makeOutput(int argc, char **argv, Opts op, pcre *compiledReg) {
  Result err = OK;
  int cntFiles = argc - op.endIndex;

  for (int i = 0; i < cntFiles; i++) {
    int cntMatch = 0;
    char *fileName = argv[op.endIndex + i];
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
      if (!op.noMessages) {
        printf("grep: %s: No such file or directory\n", fileName);
      }
      err = INVALID_FILE;
      continue;
    }

    int cntStr = 0;
    size_t len = 0;
    ssize_t nread;
    int ovector[30];
    char *buffer = NULL;
    while ((nread = getline(&buffer, &len, file)) != -1) {
      cntStr++;
      int matches =
          pcre_exec(compiledReg, NULL, buffer, nread, 0, 0, ovector, 30);

      if (printFileName(op, matches, cntFiles, fileName))
        break;

      char *lineToPrint = NULL;
      lineToPrint =
          op.onlyMatching ? makeStr(matches, ovector, buffer) : buffer;
      printStr(matches, lineToPrint, op, &cntMatch, cntStr);

      if (op.onlyMatching) {
        free(lineToPrint);
      }
      memset(buffer, 0, len);
    }

    free(buffer);
    printCntMatch(op, cntMatch, cntFiles, fileName);
    fclose(file);
  }
  pcre_free(compiledReg);
  return err;
}