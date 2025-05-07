CC = gcc
CFLAGS = -O2 -Wall -Wextra -arch arm64 -Iinclude
AR = ar
RANLIB = ranlib

SRC_DIR = src
INC_DIR = include
BUILD_DIR = lib
OBJ_DIR = $(BUILD_DIR)/obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
LIB = $(BUILD_DIR)/libcpmio.a

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB)

$(OBJ_DIR)/termansi.o: $(INC_DIR)/termcore.h
$(OBJ_DIR)/termvt52.o: $(INC_DIR)/termcore.h
$(OBJ_DIR)/cpmio.o: $(INC_DIR)/cpmio.h