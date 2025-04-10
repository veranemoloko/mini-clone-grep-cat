#define _GNU_SOURCE
#include "grep.h"

#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/resType.h"
#include "options.h"

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
  // free(reg);
  return res;
}

void printStr(int matches, char *input, Op op, int *cntMatch, int cntStr) {
  if (((matches >= 0) && !op.invertMatch) ||
      ((matches < 0) && op.invertMatch)) {
    (*cntMatch)++;
    if (!op.countMatch && !op.filesMatch) {
      if (op.lineNumber) {
        printf("%d:%s", cntStr, input);
      } else {
        printf("%s", input);
      }
    }
  }
}

void printCntMatch(Op op, int cntMatch, int cntFiles, char *fileName) {
  if (cntFiles > 1 && op.countMatch && !op.noFileName) printf("%s:", fileName);
  if (op.countMatch) printf("%d\n", cntMatch);
}

bool printFileName(Op op, int matches, int cntFiles, char *fileName) {
  bool isBreak = false;
  bool matched = (matches > 0);

  if (op.invertMatch) {
    matched = !matched;
  }

  if (op.filesMatch && matched) {
    printf("%s\n", fileName);
    isBreak = true;
  } else if (matched && cntFiles > 1 && !op.filesMatch && !op.countMatch &&
             !op.noFileName) {
    printf("%s:", fileName);
  }

  return isBreak;
}

char *makeStr(int matches, int *ovector, char *input) {
  size_t len = strlen(input);
  char *newStr = malloc(len + 2);
  if (newStr != NULL) {
    int newSize = 0;
    for (int i = 0; i < matches; i++) {
      for (int j = ovector[i * 2]; j < ovector[(i * 2) + 1]; j++) {
        newStr[newSize++] = input[j];
      }
    }
    newStr[newSize] = '\n';
    newStr[newSize + 1] = '\0';
  }
  return newStr;
}

Result fileOpenGrep(FILE **file, char *fileName, bool noMessages) {
  Result res = OK;
  *file = fopen(fileName, "r");
  if (*file == NULL) {
    if (!noMessages) {
      printf("grep: %s: No such file or directory\n", fileName);
    }
    res = INVALID_FILE;
  }
  return res;
}

Result makeOutput(int argc, char **argv, Op op, pcre *compiledReg) {
  Result res = OK;
  int cntFiles = argc - op.endIndex;

  for (int i = 0; i < cntFiles; i++) {
    FILE *file;
    char *fileName = argv[op.endIndex + i];
    res = fileOpenGrep(&file, fileName, op.noMessages);
    if (res) continue;

    size_t len = 0;
    ssize_t nread;
    int ovector[30];
    char *input = NULL;
    int cntStr = 0, cntMatch = 0;
    while ((nread = getline(&input, &len, file)) != -1) {
      cntStr++;
      int matches =
          pcre_exec(compiledReg, NULL, input, nread, 0, 0, ovector, 30);

      if (printFileName(op, matches, cntFiles, fileName)) break;

      char *lineToPrint = NULL;
      lineToPrint = op.onlyMatch ? makeStr(matches, ovector, input) : input;
      printStr(matches, lineToPrint, op, &cntMatch, cntStr);

      if (op.onlyMatch) free(lineToPrint);

      memset(input, 0, len);
    }
    printCntMatch(op, cntMatch, cntFiles, fileName);
    free(input);
    fclose(file);
  }
  pcre_free(compiledReg);
  return res;
}