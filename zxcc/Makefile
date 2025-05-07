# Compiler and tools
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Iinclude -I./cpmio/include -I./cpmredir/include
LDFLAGS = -L./cpmio/lib -L./cpmredir/lib -lcpmio -lcpmredir -lncurses
AR = ar
RANLIB = ranlib

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
OBJ_DIR = obj
BIN_DIR = bin

# Programs to build
PROGRAMS := zxas zxc zxcc zxlibr zxlink

# Source files organization
UTIL_SRC := $(SRC_DIR)/util.c
ZXCC_CORE_SRCS := $(SRC_DIR)/z80.c $(SRC_DIR)/zxbdos.c $(SRC_DIR)/zxcbdos.c $(SRC_DIR)/zxdbdos.c

# Program-specific sources
ZXAS_SRCS := $(SRC_DIR)/zxas.c $(UTIL_SRC)
ZXC_SRCS := $(SRC_DIR)/zxc.c $(UTIL_SRC)
ZXLIBR_SRCS := $(SRC_DIR)/zxlibr.c $(UTIL_SRC)
ZXLINK_SRCS := $(SRC_DIR)/zxlink.c $(UTIL_SRC)
ZXCC_SRCS := $(SRC_DIR)/zxcc.c $(ZXCC_CORE_SRCS)

# Object files for each program
ZXAS_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(ZXAS_SRCS))
ZXC_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(ZXC_SRCS))
ZXCC_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(ZXCC_SRCS))
ZXLIBR_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(ZXLIBR_SRCS))
ZXLINK_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(ZXLINK_SRCS))

# Dependencies
CPMIO_LIB = ./cpmio/lib/libcpmio.a
CPMREDIR_LIB = ./cpmredir/lib/libcpmredir.a

# Build targets
.PHONY: all clean

all: $(addprefix $(BIN_DIR)/,$(PROGRAMS))

# Build dependencies first
$(CPMIO_LIB):
	$(MAKE) -C ./cpmio

$(CPMREDIR_LIB):
	$(MAKE) -C ./cpmredir

# Link programs with dependencies
$(BIN_DIR)/zxas: $(ZXAS_OBJS) | $(CPMIO_LIB) $(CPMREDIR_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/zxc: $(ZXC_OBJS) | $(CPMIO_LIB) $(CPMREDIR_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/zxcc: $(ZXCC_OBJS) | $(CPMIO_LIB) $(CPMREDIR_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/zxlibr: $(ZXLIBR_OBJS) | $(CPMIO_LIB) $(CPMREDIR_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/zxlink: $(ZXLINK_OBJS) | $(CPMIO_LIB) $(CPMREDIR_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Include automatically generated dependencies
-include $(wildcard $(OBJ_DIR)/*.d)

# Compilation with dependency generation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(CPMIO_LIB) $(CPMREDIR_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	$(MAKE) -C ./cpmio clean
	$(MAKE) -C ./cpmredir clean

# Explicit dependencies
$(OBJ_DIR)/zxcc.o: $(INC_DIR)/zxcc.h $(INC_DIR)/z80.h $(INC_DIR)/zxbdos.h
$(OBJ_DIR)/z80.o: $(INC_DIR)/z80.h $(INC_DIR)/z80ops.h
$(OBJ_DIR)/zxbdos.o: $(INC_DIR)/zxbdos.h $(INC_DIR)/zxcbdos.h

# Install/uninstall targets
PREFIX ?= /usr/local
BIN_INSTALL_DIR = $(PREFIX)/bin

install: all
	@echo "Installing programs to $(BIN_INSTALL_DIR)"
	@mkdir -p $(BIN_INSTALL_DIR)
	@for prog in $(PROGRAMS); do \
		install -v -m 0755 $(BIN_DIR)/$$prog $(BIN_INSTALL_DIR)/$$prog; \
	done
	@echo "Installation complete"

uninstall:
	@echo "Removing programs from $(BIN_INSTALL_DIR)"
	@for prog in $(PROGRAMS); do \
		rm -fv $(BIN_INSTALL_DIR)/$$prog; \
	done
	@echo "Uninstallation complete"