# mini-clone-grep-cat
This project implements two popular Unix/Linux commands, cat and grep, in C. 

### `cat` Command
Cat - concatenate files and print on the standard output.

## Options:
 -b, --number-nonblank (overrides -n) \
 -n, --number \
 -e   (equivalent to -vE) \
 -E, --show-ends \
 -s, --squeeze-blank \
 -t (equivalent to -vT) \
 -T, --show-tabs \
 -v, --show-nonprinting (use ^ and M- notation, except for LFD and TAB) \

### `grep` Command
The `grep` command searches for lines in files that match a given pattern, using regular expressions.

## Options:
 -e PATTERNS, --regexp=PATTERNS \
 -f FILE, --file=FILE \
 -i, --ignore-case \
 -v, --invert-match \
 -c, --count \
 -l, --files-with-matches \
 -o, --only-matching \
 -s, --no-messages \
 -h, --no-filename \
 -n, --line-number \

Build and Run
 Clone the repository:
- git clone https://github.com/veranemoloko/mini-clone-grep-cat.git
- cd mini-clone-grep-cat

To build the programs:
- make
- make s21_cat
- make s21_grep

To run the programs:
- ./src/cat/s21_cat <file1> <file2> ...
- ./src/grep/s21_grep "<pattern>" <file1> <file2> ...

To run the tests:
- make test_cat
- make test_grep

To execute the test programs:
- ./tests/test_cat
- ./tests/test_grep


