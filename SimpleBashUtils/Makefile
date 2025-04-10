CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g

SRC_DIR = src
SRC_DIR_TEST = tests

SRC_CAT = main.c options.c cat.c parse.c
SRC_GREP = main.c options.c parse.c grep.c
SRC_COMMON = resType.c 
SRC_TEST_CAT = test_cat.c testFoo.c
SRC_TEST_GREP = test_grep.c testFoo.c

CSRC_CAT = $(addprefix $(SRC_DIR)/cat/,$(SRC_CAT))
CSRC_GREP = $(addprefix $(SRC_DIR)/grep/,$(SRC_GREP))
CSRC_COMMON = $(addprefix $(SRC_DIR)/common/,$(SRC_COMMON))
CSRC_TEST_CAT = $(addprefix $(SRC_DIR_TEST)/,$(SRC_TEST_CAT))
CSRC_TEST_GREP = $(addprefix $(SRC_DIR_TEST)/,$(SRC_TEST_GREP))

COBJ_CAT = $(CSRC_CAT:.c=.o)
COBJ_GREP = $(CSRC_GREP:.c=.o)
COBJ_COMMON = $(CSRC_COMMON:.c=.o)
COBJ_TEST_CAT = $(CSRC_TEST_CAT:.c=.o)
COBJ_TEST_GREP = $(CSRC_TEST_GREP:.c=.o)

TARGET_CAT = src/cat/s21_cat
TARGET_GREP = src/grep/s21_grep
TARGET_TEST_CAT = tests/test_cat
TARGET_TEST_GREP = tests/test_grep

all: $(TARGET_CAT) $(TARGET_GREP)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: s21_cat
s21_cat: $(TARGET_CAT)

$(TARGET_CAT) : $(COBJ_CAT) $(COBJ_COMMON)
	$(CC) $^ -o $(TARGET_CAT)

.PHONY: s21_grep
s21_grep: $(TARGET_GREP)

$(TARGET_GREP) : $(COBJ_GREP) $(COBJ_COMMON)
	$(CC) $^ -o $(TARGET_GREP) -lpcre

.PHONY: test_cat
test_cat: $(TARGET_TEST_CAT)

$(TARGET_TEST_CAT) : $(COBJ_TEST_CAT)
	$(CC) $^ -o $(TARGET_TEST_CAT)

.PHONY: test_grep
test_grep: $(TARGET_TEST_GREP)

$(TARGET_TEST_GREP) : $(COBJ_TEST_GREP)
	$(CC) $^ -o $(TARGET_TEST_GREP)

.PHONY: clean
clean:
	rm -f $(COBJ_CAT) $(COBJ_GREP) $(COBJ_COMMON) $(COBJ_TEST_CAT) $(COBJ_TEST_GREP) \
	$(TARGET_CAT) $(TARGET_GREP) $(TARGET_TEST_CAT) $(TARGET_TEST_GREP)


.PHONY: clangcheck
clangcheck:
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -style=file -n {} +

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem src/

.PHONY: leakscheck/cat
leakscheck/cat:
	valgrind --tool=memcheck --leak-check=yes $(TARGET_CAT)

.PHONY: leakscheck/grep
leakscheck/grep:
	valgrind --tool=memcheck --leak-check=yes $(TARGET_GREP)