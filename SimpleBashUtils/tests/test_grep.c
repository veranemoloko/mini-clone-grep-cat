#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testFoo.h"

int main() {
  int result;
  int cntResult = 1;
  int cntSuccessRes = 0;

  const char *outGrep = "grep_output.txt";
  const char *out21Grep = "s21_grep_output.txt";
  const char *inputFile = "./tests/input/text.txt ./tests/input/text2.txt";

  char *flags[] = {NULL,

                   "-i ",
                   "-v",
                   "-c",
                   "-l",
                   "-n",
                   "-h",
                   "-f ./tests/input/reg",
                   "-e \"!\" -e \"0\"",
                   "-iv",
                   "-in",
                   "-vc",
                   "-on",
                   "-oc",
                   "-ov",
                   "-vc",
                   "-vn",
                   "-s no.txt"};

  int cntTests = sizeof(flags) / sizeof(flags[0]);

  char cmdS21[1024];
  char cmdGrep[1024];

  for (int i = 0; i < cntTests; i++) {
    if (flags[i] == NULL) {
      snprintf(cmdS21, sizeof(cmdS21), "./src/grep/s21_grep \"wom\" %s > %s",
               inputFile, out21Grep);
      snprintf(cmdGrep, sizeof(cmdGrep), "grep \"wom\" %s > %s", inputFile,
               outGrep);
    } else if (strcmp(flags[i], "-f ./tests/input/reg") ||
               strcmp(flags[i], "-e \"!\" -e \"0\"")) {
      snprintf(cmdS21, sizeof(cmdS21), "./src/grep/s21_grep %s %s > %s",
               flags[i], inputFile, out21Grep);
      snprintf(cmdGrep, sizeof(cmdGrep), "grep %s %s > %s", flags[i], inputFile,
               outGrep);
    } else if (strcmp(flags[i], "-s no.txt")) {
      snprintf(cmdS21, sizeof(cmdS21), "./src/grep/s21_grep \"wom\" %s > %s",
               flags[i], out21Grep);
      snprintf(cmdGrep, sizeof(cmdGrep), "grep \"wom\" %s > %s", flags[i],
               outGrep);
    } else {
      snprintf(cmdS21, sizeof(cmdS21), "./src/grep/s21_grep %s %s > %s",
               flags[i], inputFile, out21Grep);
      snprintf(cmdGrep, sizeof(cmdGrep), "grep %s %s > %s", flags[i], inputFile,
               outGrep);
    }

    system(cmdS21);
    system(cmdGrep);
    fflush(stdout);

    result = compare_files(outGrep, out21Grep);
    printResult(flags[i] ? flags[i] : "no flags", result, cntResult++);

    if (result) cntSuccessRes++;

    remove(out21Grep);
    remove(outGrep);
  }

  printf("\nTOTAL PASSED: %d/%d\n", cntSuccessRes, cntTests);
  return 0;
}
