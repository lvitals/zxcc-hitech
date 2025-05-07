# Makefile for Z80 projects (compatible with Sjasm and Pasmo)

# Output binary file (.bin)
TARGET = bios.bin

# Source file (.zsm or .asm)
SOURCE = bios.zsm

# Default assembler (can be overridden from command line: make ASM=sjasm)
ASM ?= pasmo

# Default rule: builds the target
all: $(TARGET)

# Build rule that selects assembler based on ASM variable
$(TARGET): $(SOURCE)
ifeq ($(ASM), sjasm)
	sjasm $(SOURCE) $(TARGET)
else ifeq ($(ASM), pasmo)
	pasmo $(SOURCE) $(TARGET)
else
	@echo "Error: Unsupported assembler. Use ASM=sjasm or ASM=pasmo."
	@exit 1
endif

# Clean build artifacts
clean:
	rm -f $(TARGET)

.PHONY: all clean