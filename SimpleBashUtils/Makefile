CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g

SRC_DIR = src
SRC_CAT = main.c options.c cat.c parse.c
SRC_GREP = main.c options.c parse.c grep.c
SRC_COMMON = errType.c
CSRC_CAT = $(addprefix $(SRC_DIR)/cat/,$(SRC_CAT))
CSRC_GREP = $(addprefix $(SRC_DIR)/grep/,$(SRC_GREP))
CSRC_COMMON = $(addprefix $(SRC_DIR)/common/,$(SRC_COMMON))

COBJ_CAT = $(CSRC_CAT:.c=.o)
COBJ_GREP = $(CSRC_GREP:.c=.o)
COBJ_COMMON = $(CSRC_COMMON:.c=.o)

TARGET_CAT = src/cat/s21_cat
TARGET_GREP = src/grep/s21_grep

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

.PHONY: clean
clean:
	rm -f $(COBJ_CAT) $(COBJ_GREP) $(COBJ_COMMON) $(TARGET_CAT) $(TARGET_GREP)

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