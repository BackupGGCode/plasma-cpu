#############################################
#MAKEFILE FOR COMPILING TOOLS AND PROGRAMS FOR THE TARGET#
#############################################

#Modify the .bashrc file: export PATH=/home/xxxxxxxxxxx/mlite_project/gccmips_elf:$PATH

# The CC_X86 is for compiling tools on your PC.
CC_X86 = cl /O1 /DWIN32 /I..\tools /nologo
	

VHDL_DIR = ../vhdl
TOOLS_BIN = ./bin

# The GCC_MIPS is for compiling code on the target.
#CC_X86 = gcc -Wall -O -g
BIN_MIPS = ../gccmips_elf
GCC_MIPS  = $(BIN_MIPS)/gcc $(CFLAGS)
AS_MIPS   = $(BIN_MIPS)/as
LD_MIPS   = $(BIN_MIPS)/ld
DUMP_MIPS = $(BIN_MIPS)/objdump

# Convert_bin changes test.axf into code.txt which is used by the VHDL.
CONVERT_BIN = $(TOOLS_BIN)/convert_bin.exe

CP = cp
RM = rm -rf 
CFLAGS = -O2 -Wall -c -s 

all: convert_bin.exe tracehex.exe bintohex.exe ram_image.exe
	@echo make targets = count, opcodes, pi, test, run, tohex, \
	bootldr, toimage, etermip
	
clean:
	-$(RM) *.o *.obj *.map *.lst *.hex *.txt *.exe *.axf


convert_bin.exe: convert.c
	@$(CC_X86) -o convert_bin.exe convert.c

convert_le.exe: convert.c
	@$(CC_X86) -DLITTLE_ENDIAN -o convert_le.exe convert.c

mlite.exe: mlite.c
	@$(CC_X86) -o mlite.exe mlite.c $(DWIN32)

tracehex.exe: tracehex.c
	@$(CC_X86) -o tracehex.exe tracehex.c

bintohex.exe: bintohex.c
	@$(CC_X86) -o bintohex.exe bintohex.c

ram_image.exe: ram_image.c
	@$(CC_X86) -o ram_image.exe ram_image.c

# Terminal program that will download a new image and supports Ethernet
# traffic over UART.  Get wpcap.lib from http://www.winpcap.org/.
etermip: etermip.c
	@$(CC_X86) -o etermip.exe etermip.c wpcap.lib
	@echo Get wpcap.lib from http://www.winpcap.org/

nomult.exe: nomult.c
	-@$(CC_X86) -o nomult.exe nomult.c

download: etermip
	@echo Reset board before downloading code
	etermip

opcodes: 
	$(AS_MIPS) -o opcodes.o opcodes.asm
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf opcodes.o
	-@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

opcodes2: 
	$(AS_MIPS) -o opcodes.o opcodes.asm
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf opcodes.o
	-@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

test: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) test.c
	$(GCC_MIPS) no_os.c
	$(LD_MIPS) -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o test.o no_os.o
	-@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)
	
count: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) count.c
	$(GCC_MIPS) no_os.c 
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
		boot.o count.o no_os.o 
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)
		
lcd_leds: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) lcd_leds.c
	$(GCC_MIPS) no_os.c 
	$(LD_MIPS) -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o lcd_leds.o no_os.o 
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)
	
lcd_leds_modif: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) lcd_leds_modif.c
	$(GCC_MIPS) no_os.c 
	$(LD_MIPS) -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o lcd_leds_modif.o no_os.o 
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)
	
lcd_leds_modif_clock: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) lcd_leds_modif_clock.c
	$(GCC_MIPS) no_os.c 
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
		boot.o lcd_leds_modif_clock.o no_os.o 
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

lcd: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) lcd.c
	$(GCC_MIPS) no_os.c 
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
		boot.o lcd.o no_os.o 
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

count_le: 
	$(AS_MIPS) -EL -o boot.o boot.asm
	$(GCC_MIPS) -EL count.c
	$(GCC_MIPS) -EL no_os.c 
	$(LD_MIPS) -EL -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o count.o no_os.o 
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

count2:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) count.c
	$(GCC_MIPS) no_os.c
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
		boot.o count.o no_os.o
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

count3:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) count.c
	$(GCC_MIPS) no_os.c
	$(LD_MIPS) -Ttext 0x1000 -eentry -Map test.map -s -N -o test.axf \
		boot.o count.o no_os.o
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

count5: nomult.exe
	$(AS_MIPS) -o boot.o boot.asm
	$(AS_MIPS) -o mult_sim.o mult_sim.asm
	$(GCC_MIPS) count.c
	$(GCC_MIPS) no_os.c
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
		boot.o mult_sim.o count.o no_os.o
	-$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CP) test.axf test_old.axf
	nomult test.axf test.lst test.map
	-$(DUMP_MIPS) --disassemble test.axf > test2.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

pi: 
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) pi.c
	$(LD_MIPS) -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o pi.o 
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

pi2:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) pi.c
	$(LD_MIPS) -Ttext 0x10000000 -eentry -Map test.map -s -N -o test.axf \
		boot.o pi.o 
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

pi5: nomult.exe
	$(AS_MIPS) -o boot.o boot.asm
	$(AS_MIPS) -o mult_sim.o mult_sim.asm
	$(GCC_MIPS) pi.c
	$(LD_MIPS) -Ttext 0x0 -eentry -Map test.map -s -N -o test.axf \
		boot.o mult_sim.o pi.o 
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	nomult test.axf test.lst test.map
	@$(DUMP_MIPS) --disassemble test.axf > test2.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

ddr_test:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) ddr_init.c -DDDR_TEST_MAIN
	$(GCC_MIPS) no_os.c
	$(LD_MIPS) -Ttext 0x0 -eentry -Map test.map -s -N -o test.axf \
		boot.o ddr_init.o no_os.o
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

memtest:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) memtest.c
	$(LD_MIPS) -Ttext 0x1000 -eentry -o test.axf boot.o memtest.o
	$(CONVERT_BIN)
	
memtest2:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) -DINIT_DDR memtest.c
	$(GCC_MIPS) ddr_init.c
	$(LD_MIPS) -Ttext 0x0 -eentry -o test.axf boot.o memtest.o ddr_init.o
	$(CONVERT_BIN)

memtest3:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) memtest.c
	$(LD_MIPS) -Ttext 0x10000000 -eentry -o test.axf boot.o memtest.o
	$(CONVERT_BIN)

bootldr:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) bootldr.c
	$(GCC_MIPS) no_os.c
	$(GCC_MIPS) -DDLL_DISABLE ddr_init.c
	$(LD_MIPS) -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o bootldr.o no_os.o ddr_init.o
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)
	@echo Next do "make toimage" or "make tohex".

bootldr2:
	$(AS_MIPS) -o boot.o boot.asm
	$(GCC_MIPS) bootldr.c
	$(GCC_MIPS) no_os.c
	$(GCC_MIPS) -DDLL_DISABLE ddr_init.c
	$(LD_MIPS) -Ttext 0x1000 -eentry -Map test.map -s -N -o test.axf \
		boot.o bootldr.o no_os.o ddr_init.o
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(CONVERT_BIN)
	$(CP) code.txt $(VHDL_DIR)

bootldr_little_endian: convert_le.exe
	$(AS_MIPS) -EL -o boot.o boot.asm
	$(GCC_MIPS) -EL bootldr.c
	$(GCC_MIPS) -EL no_os.c
	$(GCC_MIPS) -EL ddr_init.c
	$(LD_MIPS) -EL -Ttext 0 -eentry -Map test.map -s -N -o test.axf \
		boot.o bootldr.o no_os.o ddr_init.o
	@$(DUMP_MIPS) --disassemble test.axf > test.lst
	$(TOOLS_BIN)/convert_le.exe
	$(CP) code.txt $(VHDL_DIR)

# Run a MIPS opcode simulator
run: mlite.exe
	@$(TOOLS_BIN)/mlite.exe test.bin 

run_little_endian: mlite.exe
	@$(TOOLS_BIN)/mlite.exe test.bin L

disassemble: mlite.exe
	$(TOOLS_BIN)/mlite.exe test.bin BD > test.txt

# Used by Altera FPGAs for ram image
tohex: bintohex.exe
	$(TOOLS_BIN)/bintohex.exe test.bin
	$(CP) code*.hex $(VHDL_DIR)

# Used by Xilinx FPGAs for ram image
toimage:
	$(TOOLS_BIN)/ram_image.exe ../vhdl/ram_xilinx.vhd ../vhdl/code.txt ../vhdl/ram_image.vhd


