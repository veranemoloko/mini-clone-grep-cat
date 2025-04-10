#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

typedef struct {
  bool numberNonblank;
  bool numberAll;
  bool squeezeBlank;
  bool showTab;
  bool showEnds;
  bool showNonprinting;
  int endIndex;
} Op;

Op newConfigs();

typedef struct {
  int strCnt;
  int emptyStrCnt;
  bool newLine;
  bool firstLine;
} LineStats;

LineStats newLineStats();

#endif