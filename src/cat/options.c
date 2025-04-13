#include "options.h"

#include <stdbool.h>

Op newConfigs() {
  return (Op){.numberAll = false,
              .numberNonblank = false,
              .showEnds = false,
              .showTab = false,
              .squeezeBlank = false,
              .showNonprinting = false,
              .endIndex = 0};
}

LineStats newLineStats() {
  return (LineStats){
      .emptyStrCnt = 0, .strCnt = 1, .firstLine = false, .newLine = false};
}
