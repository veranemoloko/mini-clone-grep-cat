# mini-clone-grep-cat
This project implements two popular Unix/Linux commands, cat and grep, in C. 

### `cat` Command 🐱
Cat - concatenate files and print on the standard output.

## Options:
- -b, --number-nonblank    Number non-empty lines (overrides -n)  
- -n, --number             Number all output lines  
- -e                       Equivalent to -vE  
- -E, --show-ends          Display $ at end of each line  
- -s, --squeeze-blank      Suppress repeated empty lines  
- -t                       Equivalent to -vT  
- -T, --show-tabs          Display TAB characters as ^I  
- -v, --show-nonprinting   Use ^ and M- notation for non-printing chars

### `grep` Command 🔍
Grep - print lines that match patterns.

## Options:
- -e PATTERNS, --regexp=PATTERNS  Use PATTERNS for matching  
- -f FILE, --file=FILE            Take PATTERNS from FILE  
- -i, --ignore-case               Case insensitive matching  
- -v, --invert-match              Select non-matching lines  
- -c, --count                     Print only match counts  
- -l, --files-with-matches        Print only matching filenames  
- -o, --only-matching             Show only matching parts  
- -s, --no-messages               Suppress error messages  
- -h, --no-filename               Suppress filename prefix  
- -n, --line-number               Print line numbers

## Build and Run
```bash
git clone https://github.com/veranemoloko/mini-clone-grep-cat.git
cd mini-clone-grep-cat

# Build all
make

# Individual builds
make s21_cat
make s21_grep

# Run
./src/cat/s21_cat [options] [file...]
./src/grep/s21_grep [options] PATTERN [file...]

# Tests
make test_cat && ./tests/test_cat
make test_grep && ./tests/test_grep
```


