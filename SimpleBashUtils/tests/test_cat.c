#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testFoo.h"

int main() {
  int result;
  int cntResult = 1;
  int cntSuccessRes = 0;

  const char *outCat = "cat_output.txt";
  const char *out21Cat = "s21_cat_output.txt";
  const char *inputFile = "./tests/input/text.txt ./tests/input/text2.txt";

  char *flags[] = {NULL, "-b",  "-e",  "-E",  "-n",  "-b",  "-s",   "-t", "-T",
                   "-v", "-tv", "-ev", "-bn", "-sb", "-sn", "-evT", "-b"};

  int cntTests = sizeof(flags) / sizeof(flags[0]);

  char cmdS21[512];
  char cmdCat[512];

  for (int i = 0; i < cntTests; i++) {
    if (flags[i] == NULL) {
      snprintf(cmdS21, sizeof(cmdS21), "./src/cat/s21_cat %s > %s", inputFile,
               out21Cat);
      snprintf(cmdCat, sizeof(cmdCat), "cat %s > %s", inputFile, outCat);
    } else {
      snprintf(cmdS21, sizeof(cmdS21), "./src/cat/s21_cat %s %s > %s", flags[i],
               inputFile, out21Cat);
      snprintf(cmdCat, sizeof(cmdCat), "cat %s %s > %s", flags[i], inputFile,
               outCat);
    }

    system(cmdS21);
    system(cmdCat);

    result = compare_files(outCat, out21Cat);
    printResult(flags[i] ? flags[i] : "no flags", result, cntResult++);

    if (result) cntSuccessRes++;

    if (i < cntTests - 1) {
      remove(out21Cat);
      remove(outCat);
    }
  }

  printf("\nTOTAL PASSED: %d/%d\n", cntSuccessRes, cntTests);
  return 0;
}
