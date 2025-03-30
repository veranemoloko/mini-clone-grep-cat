#include "options.h"
#include <stdbool.h>

Opts newConfigs() {
  return (Opts){.pattern = false,
                .ignoreCase = false,
                .invertMatch = false,
                .countMatch = false,
                .filesMatch = false,
                .lineNumber = false,
                .endIndex = 0};
}
