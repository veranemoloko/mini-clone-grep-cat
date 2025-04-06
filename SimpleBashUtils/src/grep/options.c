#include "options.h"
#include <stdbool.h>

Op newConfigs() {
  return (Op){.pattern = false,
              .ignoreCase = false,
              .invertMatch = false,
              .countMatch = false,
              .filesMatch = false,
              .lineNumber = false,
              .noFileName = false,
              .noMessages = false,
              .regFromFile = false,
              .onlyMatch = false,
              .endIndex = 0};
}
