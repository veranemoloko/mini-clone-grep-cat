#include "testFoo.h"

#include <stdio.h>
#include <stdlib.h>

void printResult(const char *test, int res, int cntRes) {
  if (res)
    printf("TEST %d: SUCCESS (%s)\n", cntRes, test);
  else
    printf("TEST %d: FAIL (%s)\n", cntRes, test);
}

int compare_files(const char *filename1, const char *filename2) {
  FILE *file1 = fopen(filename1, "r");
  FILE *file2 = fopen(filename2, "r");

  if (file1 == NULL || file2 == NULL) {
    return FAIL;
  }
  int ch1, ch2;
  do {
    ch1 = fgetc(file1);
    ch2 = fgetc(file2);
    if (ch1 != ch2) {
      fclose(file1);
      fclose(file2);
      return FAIL;
    }
  } while (ch1 != EOF && ch2 != EOF);
  fclose(file1);
  fclose(file2);
  return SUCCESS;
}