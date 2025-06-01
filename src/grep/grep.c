#define _GNU_SOURCE
#include "grep.h"

#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/resType.h"
#include "options.h"

// Compiles a regular expression pattern using PCRE library
Result regCompile(char *reg, pcre **compReg, bool ignoreCase) {
  Result res = OK;
  int erroffset;
  const char *error;
  int prce_op = ignoreCase ? PCRE_CASELESS : 0;
  *compReg = pcre_compile(reg, prce_op, &error, &erroffset, NULL);
  if (*compReg == NULL) {
    printf("Error: %s\nIndex error: %d\n", error, erroffset);
    res = INVALID_REG;
  }
  return res;
}

// Prints the string if it matches the pattern according to options
// Updates match count if there's a match
void printStr(int matches, char *input, Op op, int *matchCnt, int strCnt) {
  if (((matches >= 0) && !op.invertMatch) ||
      ((matches < 0) && op.invertMatch)) {
    (*matchCnt)++;
    if (!op.countMatch && !op.filesMatch) {
      if (op.lineNumber) {
        printf("%d:%s", strCnt, input);
      } else {
        printf("%s", input);
      }
    }
  }
}

// Prints the count of matches if countMatch option is enabled
void printCntMatch(Op op, int matchCnt, int cntFiles, char *fileName) {
  if (cntFiles > 1 && op.countMatch && !op.noFileName)
    printf("%s:", fileName);
  if (op.countMatch)
    printf("%d\n", matchCnt);
}

// Prints filename if filesMatch option is enabled or if multiple files are
// processed Returns true if processing should break after printing filename
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

// Creates a new string containing only the matched portion of input
char *makeOnlyMatchStr(int *ovector, char *input) {
  size_t len = strlen(input);
  char *newStr = malloc(len + 1);
  if (newStr != NULL) {
    int newSize = 0;
    for (int j = ovector[0]; j < ovector[1]; j++) {
      newStr[newSize++] = input[j];
    }
    newStr[newSize++] = '\n';
    newStr[newSize] = '\0';
  }
  return newStr;
}

Result fileOpenGrep(FILE **file, char *fileName, bool noMessages) {
  Result res = OK;
  *file = fopen(fileName, "r");
  if (*file == NULL) {
    if (!noMessages)
      printf("grep: %s: No such file or directory\n", fileName);
    res = INVALID_FILE;
  }
  return res;
}

void printOutput(FILE *file, int cntFiles, char *fileName, Op op,
                 pcre *compReg) {
  int strCnt = 0;
  int matchCnt = 0;

  size_t len = 0;
  ssize_t nread;
  int ovector[30];
  char *input = NULL;
  while ((nread = getline(&input, &len, file)) != -1) {
    strCnt++;

    if (op.onlyMatch && !op.countMatch && !op.filesMatch) {
      int startOffset = 0;
      int matches = 1;
      // For onlyMatch option, print each matching portion separately
      while ((matches = pcre_exec(compReg, NULL, input, nread, startOffset, 0,
                                  ovector, 30)) > 0 &&
             !op.invertMatch) {
        if (cntFiles > 1)
          printf("%s:", fileName);
        char *lineToPrint = NULL;
        lineToPrint = makeOnlyMatchStr(ovector, input);
        printStr(matches, lineToPrint, op, &matchCnt, strCnt);
        free(lineToPrint);
        startOffset = ovector[1];
      }
    } else {
      // Normal matching behavior
      int matches = pcre_exec(compReg, NULL, input, nread, 0, 0, ovector, 30);
      if (printFileName(op, matches, cntFiles, fileName))
        break;
      printStr(matches, input, op, &matchCnt, strCnt);
    }
    memset(input, 0, len);
  }
  printCntMatch(op, matchCnt, cntFiles, fileName);
  free(input);
}

// Main function that processes all input files and generates output
Result makeOutput(int argc, char **argv, Op op, pcre *compReg) {
  Result res = OK;

  for (int i = 0; i < argc - op.endIndex; i++) {
    FILE *file;
    res = fileOpenGrep(&file, argv[op.endIndex + i], op.noMessages);
    if (res)
      continue;

    printOutput(file, argc - op.endIndex, argv[op.endIndex + i], op, compReg);

    fclose(file);
  }

  pcre_free(compReg);
  return res;
}