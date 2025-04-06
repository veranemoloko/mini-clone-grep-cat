#include "parse.h"
#include "../common/resType.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Result initReg(char **reg, char *arg) {
  Result res = OK;
  *reg = malloc(strlen(arg) + 1);
  if (*reg == NULL) {
    res = MEM_ERR;
  } else {
    strcpy(*reg, arg);
  }
  return res;
}

Result buildReg(char **reg, char *arg) {
  Result res = OK;
  char *resReg;
  resReg = malloc(strlen(*reg) + strlen(arg) + 2);
  if (resReg == NULL) {
    res = MEM_ERR;
  } else {
    strcpy(resReg, *reg);
    strcat(resReg, "|");
    strcat(resReg, arg);
    free(*reg);
    *reg = resReg;
  }
  return res;
}

void replaceNewLine(char **text, size_t size) {
  size_t i = 0;
  while (i <= size) {
    if ((*text)[i] == '\n')
      (*text)[i] = '|';
    i++;
  }
}

Result fileRead(char **buffer, long size, FILE *file) {
  Result res = OK;
  *buffer = malloc(size + 1);
  if (buffer == NULL) {
    res = MEM_ERR;
  } else {
    fread(*buffer, sizeof(char), size + 1, file);
    (*buffer)[size] = '\0';
    replaceNewLine(buffer, size);
  }
  fclose(file);
  return res;
}

Result fileOpen(char *fileName, long *size, FILE **file) {
  Result res = OK;
  *file = fopen(fileName, "rb");
  if (*file == NULL) {
    printf("grep: %s: No such file or directory\n", fileName);
    res = INVALID_FILE;
  } else {
    fseek(*file, 0, SEEK_END);
    *size = ftell(*file);
    fseek(*file, 0, SEEK_SET);
  }
  return res;
}

typedef enum {
  BUILD_REG_INIT,
  BUILD_REG_FILE_OPENED,
  BUILD_REG_FILE_READ,
  BUILD_REG_BUILT
} MakeRegState;

Result initRegFile(char **reg, char *arg) {
  Result res = OK;
  long size;
  FILE *file = NULL;
  MakeRegState state = BUILD_REG_INIT;
  while (res == OK && state != BUILD_REG_FILE_READ) {
    switch (state) {
    case BUILD_REG_INIT:
      res = fileOpen(arg, &size, &file);
      state = BUILD_REG_FILE_OPENED;
      break;
    case BUILD_REG_FILE_OPENED:
      res = fileRead(reg, size, file);
      state = BUILD_REG_FILE_READ;
      break;
    default:
      break;
    }
  }
  return res;
}

Result buildRegFile(char **reg, char *arg) {
  Result res = OK;
  long size;
  char *buffer;
  FILE *file = NULL;
  MakeRegState state = BUILD_REG_INIT;
  while (res == OK && state != BUILD_REG_BUILT) {
    switch (state) {
    case BUILD_REG_INIT:
      res = fileOpen(arg, &size, &file);
      state = BUILD_REG_FILE_OPENED;
      break;
    case BUILD_REG_FILE_OPENED:
      res = fileRead(&buffer, size, file);
      state = BUILD_REG_FILE_READ;
      break;
    case BUILD_REG_FILE_READ:
      res = buildReg(reg, buffer);
      state = BUILD_REG_BUILT;
      free(buffer);
    case BUILD_REG_BUILT:
      break;
    }
  }
  return res;
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

Result parseOptions(int argc, char **argv, Op *op, char **reg) {
  Result res = OK;
  int encodedArg;
  while (res == OK && (encodedArg = getopt_long(argc, argv, "e:ivclnhsf:o",
                                                longOpts, NULL)) != -1) {

    switch (encodedArg) {
    case 'e':
      op->pattern = true;
      res = *reg != NULL ? buildReg(reg, optarg) : initReg(reg, optarg);
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
      res = *reg != NULL ? buildRegFile(reg, optarg) : initRegFile(reg, optarg);
      break;
    case 'o':
      op->onlyMatch = true;
      break;
    default:
      res = INVALID_REG;
    }
  };

  if (argc <= optind)
    res = USAGE;

  op->endIndex = (op->pattern || op->regFromFile) ? optind : optind + 1;
  *reg = (op->pattern || op->regFromFile) ? *reg : argv[optind];

  return res;
}