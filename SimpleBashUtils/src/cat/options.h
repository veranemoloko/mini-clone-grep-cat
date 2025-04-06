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

#endif