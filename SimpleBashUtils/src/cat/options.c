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
