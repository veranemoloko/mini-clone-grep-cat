#include "parse.h"
#include "../common/errType.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ErrTypes initReg(char **reg, char *arg) {
  ErrTypes err = OK;
  *reg = malloc(strlen(arg) + 1);
  if (*reg == NULL) {
    err = MEM_ERR;
  } else {
    strcpy(*reg, arg);
  }
  return err;
}

ErrTypes buildReg(char **reg, char *arg) {
  ErrTypes err = OK;
  char *resReg;
  resReg = malloc(strlen(*reg) + strlen(arg) + 2);
  if (resReg == NULL) {
    err = MEM_ERR;
  } else {
    strcpy(resReg, *reg);
    strcat(resReg, "|");
    strcat(resReg, arg);
    free(*reg);
    *reg = resReg;
  }
  return err;
}

void replaceNewLine(char **text, size_t size) {
  size_t i = 0;
  while (i <= size) {
    if ((*text)[i] == '\n')
      (*text)[i] = '|';
    i++;
  }
}

ErrTypes fileRead(char **buffer, long size, FILE *file) {
  ErrTypes err = OK;
  *buffer = malloc(size + 1);
  if (buffer == NULL) {
    err = MEM_ERR;
  } else {
    fread(*buffer, sizeof(char), size + 1, file);
    replaceNewLine(buffer, size);
  }
  return err;
}

ErrTypes fileOpen(char *fileName, long *size, FILE **file) {
  ErrTypes err = OK;
  *file = fopen(fileName, "rb");
  if (*file == NULL) {
    err = INVALID_FILE;
  } else {
    fseek(*file, 0, SEEK_END);
    *size = ftell(*file);
    fseek(*file, 0, SEEK_SET);
  }
  return err;
}

ErrTypes initRegFile(char **reg, char *arg) {
  ErrTypes err;
  long size;
  FILE *file = NULL;

  return ((err = fileOpen(arg, &size, &file)) ||
          (err = fileRead(reg, size, file)))
             ? err
             : OK;
}

ErrTypes buildRegFile(char **reg, char *arg) {
  ErrTypes err;
  long size;
  char *buffer;
  FILE *file = NULL;
  return ((err = fileOpen(arg, &size, &file)) ||
          (err = fileRead(&buffer, size, file)) ||
          (err = buildReg(reg, buffer)))
             ? err
             : OK;
}

const struct option longOpts[] = {
    {"regexp", required_argument, NULL, 'e'},
    {"ignore-case", no_argument, NULL, 'i'},
    {"invert-match", no_argument, NULL, 'v'},
    {"count", no_argument, NULL, 'c'},
    {"files-with-matches", no_argument, NULL, 'l'},
    {"line-number", no_argument, NULL, 'n'},
    {"no-filename", no_argument, NULL, 'h'},
    {"no-messages", no_argument, NULL, 's'},
    {"file", required_argument, NULL, 'f'},
    {"only-matching", no_argument, NULL, 'o'},
    {0, 0, 0, 0}};

ErrTypes parseOptions(int argc, char **argv, Opts *op, char **reg) {
  ErrTypes err = OK;
  int res;

  while ((res = getopt_long(argc, argv, "e:ivclnhsf:o", longOpts, NULL)) !=
         -1) {
    switch (res) {
    case 'e':
      err = *reg != NULL ? buildReg(reg, optarg) : initReg(reg, optarg);
      op->pattern = true;
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
    case 'h':
      op->noFileName = true;
      break;
    case 's':
      op->noMessages = true;
      break;
    case 'f':
      op->regFromFile = true;
      err = *reg != NULL ? buildRegFile(reg, optarg) : initRegFile(reg, optarg);
      break;
    case 'o':
      op->onlyMatching = true;
    }
  };

  if (argc <= optind || argc == 1)
    err = INVALID_FILE;

  op->endIndex = (op->pattern || op->regFromFile) ? optind : optind + 1;
  *reg = (op->pattern || op->regFromFile) ? *reg : argv[optind];

  return err;
}