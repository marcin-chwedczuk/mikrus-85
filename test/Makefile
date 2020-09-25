REMOVE = rm -f
RENAME = mv

COMPILER = scc8080
ASSEMBLER = as8085
LINKER = aslink

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET := $(BIN_DIR)/eeprom.hex
SRC := $(wildcard $(SRC_DIR)/*.c)

#STARTADDRESS = 0x0100

# Compiler options
# usage: sccXXXX [-tcsah] [-dSYM[=VALUE]] [-l[log]] files
# -t: output c source as asm comments
# -a: no argument count in A to function calls
# -d: define macro
# -u: use undocumented 8085 instructions LDSI, LHLX, SHLX
# -s: assemble generated output, not implemented
# -c: link, not implemented
# -h: displays usage
# -l: set the log
# log - a file that you wish to contain most (if not all) messages
# files - one or more files. no filename redirects to stdin/stdout
SCCFLAGS = -t -a

# Assembler options
#Usage: [-Options] [-Option with arg] file
#Usage: [-Options] [-Option with arg] outfile file1 [file2 ...]
#  -h   or NO ARGUMENTS  Show this help list
#Output:
#  -l   Create list   file/outfile[.lst]
#  -o   Create object file/outfile[.rel]
#  -s   Create symbol file/outfile[.sym]
#Listing:
#  -d   Decimal listing
#  -q   Octal   listing
#  -x   Hex     listing (default)
#  -b   Display .define substitutions in listing
#  -bb  and display without .define substitutions
#  -c   Disable instruction cycle count in listing
#  -f   Flag relocatable references by  `   in listing file
#  -ff  Flag relocatable references by mode in listing file
#  -p   Disable automatic listing pagination
#  -u   Disable .list/.nlist processing
#  -w   Wide listing format for symbol table
#Assembly:
#  -i   Insert assembler line before input file(s)
#  -v   Enable out of range signed / unsigned errors
#Symbols:
#  -a   All user symbols made global
#  -g   Undefined symbols made global
#  -z   Disable case sensitivity for symbols
#Debugging:
#  -j   Enable NoICE Debug Symbols
#  -y   Enable SDCC  Debug Symbols
AS8085FLAGS = -gloaxspff 

# These settings control where the compiler will place the code and variables in memory.
ASLINKFLAGS = -n -i -u -o -m -b CRET=$(STARTADDRESS) -b LIB8080=crtsoend+$(STARTADDRESS) -b SMALLC_GENERATED=crun8080_end+crtsoend+$(STARTADDRESS)

# Target file name (without extension).
TARGET = eeprom.hex
LIB_SRC = main.c bdos.c chio8080.c
ASM_SRC = cret.asm crun8080lib.asm
ASM_OBJ = $(addsuffix .rel, $(basename $(ASM_SRC)))
LIB_OBJ = $(addsuffix .rel, $(basename $(LIB_SRC)))
#PATH := /cygdrive/c/Users/roman/hobby/hardware_projects/google_code/smallc_u85ls
PATH := /cygdrive/d/Users/roman/hobby/hardware_projects/smallc_rep/smallc_u85ls
PATH := $(PATH):/cygdrive/d/users/roman/hobby/hardware_projects/8085/asxv5pxx/asxmak/cygwin/exe
PATH := $(PATH):/usr/bin
PATH := $(PATH):/cygdrive/d/users/roman/hobby/hardware_projects/8085/ncb85/Utils
all: pre-build $(TARGET).hex post-build

pre-build:
	@echo 'Building project'

post-build:
	@echo 'Build finished'

$(TARGET).hex: $(LIB_OBJ) $(ASM_OBJ)
	$(LINKER) $(ASLINKFLAGS) $(TARGET) $(ASM_OBJ) $(LIB_OBJ)
	$(SORTHEX) $(TARGET).ihx > $(TARGET).hex
	$(HEX2COM) $(TARGET).hex

%.s: %.c
	$(COMPILER) $(SCCFLAGS) $<
	
%.rel: %.c
	$(COMPILER) $(SCCFLAGS) $<
	$(ASSEMBLER) $(AS8085FLAGS) $(addsuffix .s, $(basename $<))

%.rel: %.asm
	$(ASSEMBLER) $(AS8085FLAGS) $<

clean:
	@echo 'Cleaning project'
	$(REMOVE) *.ihx *.hex *.s *.mem *.rel *.map *.sym *.lst *.rst *.lnk \
	*.x *.com *.bin

