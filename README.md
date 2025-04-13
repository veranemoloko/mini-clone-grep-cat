# mini-clone-grep-cat
This project implements two popular Unix/Linux commands, cat and grep, in C. These basic utilities allow for reading file contents and searching text within files using patterns, respectively. The project demonstrates how to recreate these commands with basic functionality.
## Description

### `cat` Command
The `cat` command reads and outputs the contents of one or more files to the standard output (typically the terminal).

### `grep` Command
The `grep` command searches for lines in files that match a given pattern, using regular expressions.

# Build and Run
 Clone the repository:
- git clone https://github.com/veranemoloko/mini-clone-grep-cat.git
- cd mini-clone-grep-cat

#To build the programs:
- make
- make s21_cat
- make s21_grep

#To run the programs:
- ./src/cat/s21_cat <file1> <file2> ...
- ./src/grep/s21_grep "<pattern>" <file1> <file2> ...

#To run the tests:
- make test_cat
- make test_grep

#To execute the test programs:
- ./tests/test_cat
- ./tests/test_grep


