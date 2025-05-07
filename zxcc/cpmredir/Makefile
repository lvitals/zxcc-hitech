# Compiler and tools
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Iinclude
AR = ar
RANLIB = ranlib
MKDIR = mkdir -p
RM = rm -rf

# Detect system architecture
UNAME_M := $(shell uname -m)

# Architecture-specific flags
ifeq ($(UNAME_M),arm64)
    CFLAGS += -arch arm64
else ifeq ($(UNAME_M),x86_64)
    CFLAGS += -march=native
endif

# Directory structure
SRC_DIR = src
INC_DIR = include
BUILD_DIR = lib
OBJ_DIR = $(BUILD_DIR)/obj
LIB_TARGET = $(BUILD_DIR)/libcpmredir.a

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.d,$(SRCS))

# Build targets
.PHONY: all clean

all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJS)
	@$(MKDIR) $(BUILD_DIR)
	$(AR) rcs $@ $^
	$(RANLIB) $@

# Include automatically generated dependencies
-include $(DEPS)

# Compilation with dependency generation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Clean
clean:
	$(RM) $(OBJ_DIR) $(LIB_TARGET)

# Explicit dependencies (add your specific header dependencies here)
$(OBJ_DIR)/fcb_open.o: $(INC_DIR)/cpmredir.h
$(OBJ_DIR)/fcb_close.o: $(INC_DIR)/cpmredir.h
# Add more file-specific dependencies as needed