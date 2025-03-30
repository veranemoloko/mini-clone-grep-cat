#include "options.h"
#include <stdbool.h>

Opts newConfigs() {
  return (Opts){.numberAll = false,
                .numberNonblank = false,
                .showEnds = false,
                .showTab = false,
                .squeezeBlank = false,
                .showNonprinting = false,
                .endIndex = 0};
}
