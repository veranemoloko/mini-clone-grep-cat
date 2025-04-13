#ifndef TEST_FOO_H
#define TEST_FOO_H

#define SUCCESS 1
#define FAIL 0

void printResult(const char *test, int res, int cntRes);
int compare_files(const char *filename1, const char *filename2);

#endif