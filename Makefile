# Main Makefile to build zxcc and hitech (compatible with Linux, macOS, and BSDs)

# Use gmake on BSD systems if necessary
MAKE ?= make

# Portable default commands
LN_S = ln -sf
MKDIR_P = mkdir -p
TEST = test
ECHO = echo

# Common installation paths
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib/cpm
INCDIR = $(PREFIX)/include
DOCDIR = $(PREFIX)/share/doc

# Local build paths (in user's directory)
LOCAL_PREFIX = $(CURDIR)/local
LOCAL_BINDIR = $(LOCAL_PREFIX)/bin
LOCAL_LIBDIR = $(LOCAL_PREFIX)/lib/cpm
LOCAL_BINDIR80 = $(LOCAL_LIBDIR)/bin80
LOCAL_LIBDIR80 = $(LOCAL_LIBDIR)/lib80
LOCAL_INCDIR80 = $(LOCAL_LIBDIR)/include80

# Paths for zxcc
ZXCC_DIR = $(CURDIR)/zxcc
ZXCC_BIN = $(ZXCC_DIR)/bin
ZXCC_BIOS = $(ZXCC_DIR)/bios

# zxcc environment configuration (using local paths)
export ZXCC_BIOS_PATH = $(ZXCC_BIOS)
export CPMDIR80 = $(LOCAL_LIBDIR)
export BINDIR80 = $(LOCAL_BINDIR80)
export LIBDIR80 = $(LOCAL_LIBDIR80)
export INCDIR80 = $(LOCAL_INCDIR80)

# Main targets
.PHONY: all zxcc hitech install uninstall clean

all: zxcc hitech

# Rule to build zxcc
zxcc:
	@$(ECHO) "Building zxcc..."
	$(MAKE) -C $(ZXCC_DIR) all
	@$(TEST) -f $(ZXCC_BIOS)/bios.bin || ( $(ECHO) "Error: bios.bin not found in $(ZXCC_BIOS)" && exit 1 )
	@$(MKDIR_P) $(LOCAL_BINDIR80)
	@$(LN_S) $(abspath $(ZXCC_BIOS)/bios.bin) $(LOCAL_BINDIR80)/bios.bin

# Rule to build hitech (depends on zxcc)
hitech: zxcc
	@$(ECHO) "Building hitech..."
	@$(ECHO) "Using ZXCC_BIOS_PATH=$(ZXCC_BIOS_PATH)"
	PATH="$(ZXCC_BIN):$$PATH" $(MAKE) -C hitech all

# Rule to install (requires sudo)
install: zxcc hitech
	@$(ECHO) "Installing to $(PREFIX) - may require sudo privileges"
	@$(MKDIR_P) $(DESTDIR)$(BINDIR)
	@$(MKDIR_P) $(DESTDIR)$(LIBDIR)
	@$(MKDIR_P) $(DESTDIR)$(INCDIR)
	@$(ECHO) "Installing zxcc..."
	$(MAKE) -C $(ZXCC_DIR) install PREFIX=$(PREFIX)
	@$(ECHO) "Installing hitech..."
	$(MAKE) -C hitech install PREFIX=$(PREFIX)

# Rule to uninstall (requires sudo)
uninstall:
	@$(ECHO) "Uninstalling from $(PREFIX) - may require sudo privileges"
	@$(ECHO) "Uninstalling hitech..."
	$(MAKE) -C hitech uninstall PREFIX=$(PREFIX)
	@$(ECHO) "Uninstalling zxcc..."
	$(MAKE) -C $(ZXCC_DIR) uninstall PREFIX=$(PREFIX)

# Rule to clean build artifacts
clean:
	@$(ECHO) "Cleaning hitech..."
	$(MAKE) -C hitech clean
	@$(ECHO) "Cleaning zxcc..."
	$(MAKE) -C $(ZXCC_DIR) clean
	@$(ECHO) "Removing local build directories..."
	@$(RM) -rf $(LOCAL_PREFIX)