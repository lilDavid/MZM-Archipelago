# Disable built-in rules
.SUFFIXES:

TARGET = mzm_us_ap.gba
PATCH = basepatch.bsdiff
SYMBOLS = extracted_symbols.json
BASEROM = mzm_us_baserom.gba
SHA1FILE = mzm.sha1
SYMBOL_INSTRUCTIONS = extracts.json
ELF = $(TARGET:.gba=.elf)
MAP = $(TARGET:.gba=.map)
DUMPS = $(BASEROM:.gba=.dump) $(TARGET:.gba=.dump)

# ROM header
GAME_TITLE = ZEROMISSIONE
GAME_CODE = BMXE
MAKER_CODE = 01
GAME_REVISION = 00

# Binaries
CPP = cpp
TOOLCHAIN ?= arm-none-eabi-
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump

CC = agbcc

DIFF = diff -u
HOSTCC = cc
MKDIR = mkdir -p
RM = rm -f
SHA1SUM = sha1sum
TAIL = tail

# Tools
GBAFIX = tools/gbafix/gbafix
PYTHON = python3
EXTRACTOR = tools/extractor.py
PREPROC = tools/preproc/preproc
BSDIFF = bsdiff
MAKE_CUSTOM_GRAPHICS = tools/make_graphics.py
SYMBOLEXTRACTOR = tools/extract_symbols.py

# Flags
ASFLAGS = -mcpu=arm7tdmi
CFLAGS = -Werror -O2 -mthumb-interwork -fhex-asm -f2003-patch
CPPFLAGS = -nostdinc -Iinclude/
PREPROCFLAGS = charmap.txt

# Objects
CSRC = $(wildcard src/**.c) $(wildcard src/**/**.c) $(wildcard src/**/**/**.c) $(wildcard src/**/**/**/**.c)
.PRECIOUS: $(CSRC:.c=.s)
ASMSRC = $(CSRC:.c=.s) $(wildcard asm/*.s) $(wildcard audio/*.s) $(wildcard audio/**/*.s) $(wildcard audio/**/**/*.s)
OBJ = $(ASMSRC:.s=.o) 
RANDO_GRAPHICS_SRC = $(wildcard assets/**.png)
RANDO_GRAPHICS = $(RANDO_GRAPHICS_SRC:assets/%.png=data/rando/%.gfx) $(RANDO_GRAPHICS_SRC:assets/%.png=data/rando/%.pal) $(wildcard assets/**.pal)

# Enable verbose output
ifeq ($(V),1)
	Q =
	MSG = @:
else
	Q = @
	MSG = @echo " "
endif

.PHONY: all
all: $(PATCH) $(SYMBOLS)

.PHONY: baserom
baserom: $(TARGET)

.PHONY: clean
clean:
	$(MSG) RM $(TARGET)
	$Q$(RM) $(TARGET) $(ELF) $(MAP)
	$(MSG) RM \*.dump
	$Q$(RM) $(DUMPS)
	$(MSG) RM \*.o
	$Q$(RM) $(OBJ)
	$(MSG) RM data/*.s
	$Q$(RM) $(DATA)
	$(MSG) RM src/\*\*/\*.s
	$Q$(RM) $(CSRC:.c=.s)
	$(MSG) RM $(GBAFIX)
	$Q$(RM) $(GBAFIX)
	$(MSG) RM data/
	$Q$(RM) -r data	
	$(MSG) RM $(PATCH)
	$Q$(RM) $(PATCH)
	$(MSG) RM $(SYMBOLS)
	$Q$(RM) $(SYMBOLS)

.PHONY: help
help:
	@echo 'Targets:'
	@echo '  all: create the bsdiff patch'
	@echo '  baserom: build the ROM'
	@echo '  clean: remove the patch and intermediate files'
	@echo '  help: show this message'
	@echo ''
	@echo 'Flags:'
	@echo '  V=1: enable verbose output'

$(PATCH): $(TARGET)
	$(MSG) BSDIFF $@
	$Q$(BSDIFF) $(BASEROM) $(TARGET) $(PATCH)

$(SYMBOLS): $(SYMBOLEXTRACTOR) $(SYMBOL_INSTRUCTIONS) $(TARGET)
	$(MSG) SYMBOLEXTRACTOR $@
	$Q$(PYTHON) $(SYMBOLEXTRACTOR) $(MAP) $(SYMBOLS)

$(TARGET): $(ELF) $(GBAFIX)
	$(MSG) OBJCOPY $@
	$Q$(OBJCOPY) -O binary --gap-fill 0xff --pad-to 0x08800000 $< $@
	$(MSG) GBAFIX $@
	$Q$(GBAFIX) $@ -t$(GAME_TITLE) -c$(GAME_CODE) -m$(MAKER_CODE) -r$(GAME_REVISION)

$(ELF) $(MAP): $(OBJ) linker.ld
	$(MSG) LD $@
	$Q$(LD) $(LDFLAGS) -n -T linker.ld -Map=$(MAP) -o $@

%.dump: %.gba
	$(MSG) OBJDUMP $@
	$Q$(OBJDUMP) -D -bbinary -marm7tdmi -Mforce-thumb  $< | $(TAIL) -n+3 >$@
#--stop-address 0x8c71c
%.o: %.s
	$(MSG) AS $@
	$Q$(AS) $(ASFLAGS) $< -o $@

%.s: %.c
	$(MSG) CC $@
	$Q$(PREPROC) $< $(PREPROCFLAGS) | $(CPP) $(CPPFLAGS) | $(CC) -o $@ $(CFLAGS) && printf '\t.align 2, 0 @ dont insert nops\n' >> $@

src/sram/%.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm
src/sram/%.s: src/sram/%.c

src/libgcc/%.s: CFLAGS = -O2 -fhex-asm
src/libgcc/%.s: src/libgcc/%.c

src/sprites_AI/%.s: CFLAGS = -O2 -mthumb-interwork -fhex-asm
src/sprites_AI/%.s: src/sram/%.c

src/data/rando_data.s: $(RANDO_GRAPHICS)

data/rando/%.gfx data/rando/%.pal: assets/%.png
	$Q$(MKDIR) data/rando
	$(MSG) MAKE_CUSTOM_GRAPHICS $@
	$Q$(PYTHON) $(MAKE_CUSTOM_GRAPHICS) $<

tools/%: tools/%.c
	$(MSG) HOSTCC $@
	$Q$(HOSTCC) $< $(HOSTCFLAGS) $(HOSTCPPFLAGS) -o $@
