# Makefile for Plasma RTOS and Plasma TCP/IP stack

ifeq ($(LANG),)

# Customize for Windows
# The MIPS gcc compiler must use the cygwin1.dll that came with the compiler.
CC_X86 = cl /O1 /nologo /I..\tools
CP = copy
RM = rm -rf
DWIN32 = -DWIN32
BIN_MIPS = ../gccmips_elf
TOOLS_DIR = ../tools/
TOOLS2_DIR = ../tools
APP_DIR = ../App/
LINUX_PWD =./
ALIASING  =
GCC_MIPS  = $(BIN_MIPS)/gcc $(CFLAGS)
AS_MIPS   = $(BIN_MIPS)/as
LD_MIPS   = $(BIN_MIPS)/ld
DUMP_MIPS = $(BIN_MIPS)/objdump
CONVERT_BIN = $(TOOLS_DIR)bin/convert_bin.exe
OBJ = obj
CFLAGS_X86 = /c /DWIN32
LFLAGS_X86 =

else

# Customized for Linux
# See the GNU GCC tab on the Opencores Plasma page
CC_X86 = gcc -Wall -O -g -I../tools
CP = cp
RM = rm -rf 
DWIN32 =
TOOLS_DIR = ../tools/
TOOLS2_DIR = ../tools
APP_DIR = ../App/
LINUX_PWD = ./
ALIASING  = -fno-strict-aliasing
GCC_MIPS  = mips-linux-gnu-gcc $(CFLAGS)
AS_MIPS   = mips-linux-gnu-as
LD_MIPS   = mips-linux-gnu-ld
DUMP_MIPS = mips-linux-gnu-objdump
CONVERT_BIN = $(TOOLS_DIR)convert_bin.exe
#CONVERT_BIN = $(BIN_MIPS)mips-elf-objcopy -I elf32-big -O binary test.axf test.bin
OBJ =o
CFLAGS_X86 = -c -DWIN32 -DLINUX
LFLAGS_X86 = -lm

endif

# Use software multiplier (don't use mult.vhd)
CFLAGS_SW_MULT = -mno-mul -DUSE_SW_MULT

# Use 16 fewer registers (make reg_bank.vhd smaller)
CFLAGS_FEW_REGS = -ffixed-t0 -ffixed-t1 -ffixed-t2 -ffixed-t3 -ffixed-t4 -ffixed-t5 -ffixed-t6 -ffixed-t7 -ffixed-s0 -ffixed-s1 -ffixed-s2 -ffixed-s3 -ffixed-s4 -ffixed-s5 -ffixed-s6 -ffixed-s7 

CFLAGS = -O2 -Wall -c -s -I$(TOOLS2_DIR) -msoft-float -fno-builtin
#CFLAGS += $(CFLAGS_SW_MULT)
#CFLAGS += $(CFLAGS_FEW_REGS)

# Use Ethernet for TCP/IP packets, use flash file system
rtos_tcpip_eth:
	$(AS_MIPS) -o boot.o $(TOOLS_DIR)boot.asm
	$(GCC_MIPS) rtos.c
	$(GCC_MIPS) libc.c
	$(GCC_MIPS) uart.c -DNO_PACKETS
	$(GCC_MIPS) rtos_appl.c -DINCLUDE_ETH -DINCLUDE_CONSOLE
	$(GCC_MIPS) math.c $(ALIASING)
	$(GCC_MIPS) tcpip.c -DINCLUDE_FILESYS
	$(GCC_MIPS) http.c -DINCLUDE_FILESYS -DEXAMPLE_HTML
	$(GCC_MIPS) netutil.c -DINCLUDE_FLASH -DDLL_SETUP
	$(GCC_MIPS) filesys.c -DINCLUDE_FLASH
	$(GCC_MIPS) ethernet.c
	$(GCC_MIPS) flash.c
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
	boot.o rtos.o libc.o uart.o rtos_appl.o math.o tcpip.o \
	http.o netutil.o filesys.o ethernet.o flash.o 
	$(CONVERT_BIN)
	@sort <test.map >test2.map
	@$(DUMP_MIPS) --disassemble test.axf > test.lst

clean:
	-$(RM) *.o *.obj *.axf *.map *.lst *.hex *.txt *.bin *.exe

# Run a Plasma CPU opcode simulator (can execute rtos target)
run: 
	@$(TOOLS_DIR)bin/mlite.exe test.bin 

disassemble:
	-@$(TOOLS_DIR)mlite.exe test.bin BD > test.txt

# Start the EtermIP terminal program to download the code to the Plasma CPU
# and permit an Ethernet packets to be transfered.
download:
	@echo Reset board before downloading code
	$(TOOLS_DIR)bin/etermip.exe
toimage:
	$(TOOLS_DIR)bin/ram_image.exe ../vhdl/ram_xilinx.vhd ../vhdl/code.txt ../vhdl/ram_image.vhd



