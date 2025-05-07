# Main Makefile to build zxcc and hitech (compatible with Linux, macOS, and BSDs)

# Use gmake on BSD systems if necessary
MAKE ?= make

# Portable default commands
LN_S = ln -sf
MKDIR_P = mkdir -p
TEST = test
ECHO = echo

# Common installation paths (default values, can be overridden)
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib/cpm
INCDIR ?= $(PREFIX)/include
DOCDIR ?= $(PREFIX)/share/doc

# Paths for zxcc
ZXCC_DIR = $(CURDIR)/zxcc
ZXCC_BIN = $(ZXCC_DIR)/bin
ZXCC_BIOS = $(ZXCC_DIR)/bios

# zxcc environment configuration
export ZXCC_BIOS_PATH = $(ZXCC_BIOS)
export CPMDIR80 = $(ZXCC_BIOS)
export BINDIR80 = $(ZXCC_BIOS)

# Main targets
.PHONY: all zxcc hitech install uninstall clean

all: zxcc hitech

# Rule to build zxcc
zxcc:
	@$(ECHO) "Building zxcc..."
	$(MAKE) -C $(ZXCC_DIR) all
	@$(TEST) -f $(ZXCC_BIOS)/bios.bin || ( $(ECHO) "Error: bios.bin not found in $(ZXCC_BIOS)" && exit 1 )

# Rule to build hitech (depends on zxcc)
hitech: zxcc
	@$(ECHO) "Building hitech..."
	@$(ECHO) "Using ZXCC_BIOS_PATH=$(ZXCC_BIOS_PATH)"
	PATH="$(ZXCC_BIN):$$PATH" $(MAKE) -C hitech all

# Rule to install (requires sudo)
install: zxcc hitech
	@$(ECHO) "Installing - may require sudo privileges"
	@$(ECHO) "Installing zxcc..."
	$(MAKE) -C $(ZXCC_DIR) install
	@$(ECHO) "Installing hitech..."
	PATH="$(ZXCC_BIN):$$PATH" $(MAKE) -C hitech install

# Rule to uninstall (requires sudo)
uninstall:
	@$(ECHO) "Uninstalling - may require sudo privileges"
	@$(ECHO) "Uninstalling hitech..."
	$(MAKE) -C hitech uninstall
	@$(ECHO) "Uninstalling zxcc..."
	$(MAKE) -C $(ZXCC_DIR) uninstall

# Rule to clean build artifacts
clean:
	@$(ECHO) "Cleaning hitech..."
	$(MAKE) -C hitech clean
	@$(ECHO) "Cleaning zxcc..."
	$(MAKE) -C $(ZXCC_DIR) clean