#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

typedef struct {
  bool pattern;      //-e --regexp=PATTERNS
  bool ignoreCase;   //-i --ignore-case
  bool invertMatch;  //-v --invert-match
  bool countMatch;   //-c --count
  bool filesMatch;   //-l --files-with-matches
  bool lineNumber;   //-n --line-number
  bool noFileName;   //-h --no-filename
  bool noMessages;   //-s --no-messages
  bool regFromFile;  //-f --file=FILE
  bool onlyMatching; //-o --only-matching
  int endIndex;
} Opts;

Opts newConfigs();

#endif