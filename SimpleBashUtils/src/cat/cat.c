#include "cat.h"
#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/resType.h"
#include "options.h"

bool isControlChar(unsigned char c) { return c < 32; }
bool isDelChar(unsigned char c) { return c == 127; }
bool isMetaChar(unsigned char c) { return c >= 128; }
bool isEmptyStr(char c) { return c == '\n'; }

void printEnd() { putchar('$'); }
void printTab() { printf("^I"); }
void printDel() { printf("^?"); }
void printNewLine() { putchar('\n'); }
void printEscapedMeta() { printf("M-"); }
void printControlChar(unsigned char c) { printf("^%c", c + '@'); }
void printMetaChar(unsigned char c) {
  printEscapedMeta();
  c -= 128;
  if (isControlChar(c)) {
    printControlChar(c);
  } else if (isDelChar(c)) {
    printDel();
  } else {
    putchar(c);
  }
}

void printChar(unsigned char c, bool showEnd, bool showTab) {
  if (c == '\n') {
    if (showEnd) printEnd();
    printNewLine();
  } else if (showTab && c == '\t') {
    printTab();
  } else if (!showTab && c == '\t') {
    printf("%c", c);
  } else if (isDelChar(c)) {
    printDel();
  } else if (isControlChar(c)) {
    printControlChar(c);
  } else if (isMetaChar(c)) {
    printMetaChar(c);
  } else {
    putchar(c);
  }
}

void printNoPrinting(const char *input, bool showEnd, bool showTab) {
  int c;
  for (size_t i = 0; input[i] != '\0'; i++) {
    c = (unsigned char)input[i];
    printChar(c, showEnd, showTab);
  }
}

void printTabs(char *input, bool status) {
  size_t j = 0;
  while (input[j] != '\0') {
    if (status && input[j] == '\t') {
      printTab();
    } else if (input[j] != '\n') {
      putchar(input[j]);
    }
    j++;
  }
}

void printStrCnt(Op op, LineStats *lineSt) {
  if (!lineSt->firstLine) {
    if (op.numberNonblank && !lineSt->emptyStrCnt)
      printf("%6d\t", (lineSt->strCnt)++);
    else if (op.numberAll && (!op.numberNonblank))
      printf("%6d\t", (lineSt->strCnt)++);
  }
}

Result fileOpen(FILE **file, char *fileName) {
  *file = fopen(fileName, "r");
  return (*file != NULL) ? OK : INVALID_FILE;
}

void printOutput(FILE *file, char **input, Op op, LineStats *lineSt) {
  ssize_t nread;
  size_t len = 0;
  while ((nread = getline(input, &len, file)) != -1) {
    lineSt->emptyStrCnt =
        (isEmptyStr((*input)[0])) ? lineSt->emptyStrCnt + 1 : 0;

    if (op.squeezeBlank && lineSt->emptyStrCnt >= 2) continue;

    lineSt->newLine = (*input)[(strlen(*input)) - 1] == '\n' ? true : false;

    printStrCnt(op, lineSt);

    if (!op.showNonprinting) {
      printTabs(*input, op.showTab);
      if (op.showEnds && lineSt->newLine) printEnd();
      if (lineSt->newLine) printNewLine();
    } else
      printNoPrinting(*input, op.showEnds, op.showTab);

    memset(*input, 0, len);
    lineSt->firstLine = false;
  }
}

Result makeOutput(const int argc, char **argv, const Op op) {
  Result res = OK;
  LineStats lineSt = newLineStats();

  for (int i = 0; i < argc - op.endIndex; i++) {
    FILE *file;
    res = fileOpen(&file, argv[op.endIndex + i]);
    if (res == INVALID_FILE) {
      printf("cat: %s: No such file or directory\n", argv[op.endIndex + i]);
      continue;
    }

    if (i > 0 && lineSt.newLine == false) lineSt.firstLine = true;

    char *input = NULL;
    printOutput(file, &input, op, &lineSt);

    fclose(file);
    free(input);
  }

  return res;
}
