# Makefile

CC = gcc
CFLAGS = -c -m32 -march=i486 -nostdlib 

###########################

default :
	make run

ipl10.bin : ipl10.asm
	nasm $< -o $@ -l ipl10.lst

asmhead.bin : asmhead.asm
	nasm $< -o $@ -l asmhead.lst


nasmfunc.o : nasmfunc.asm
	nasm -f elf $< -o $@ -l nasmfunc.lst

%.o : %.c
	$(CC) $(CFLAGS) $*.c -o $*.o 



#OBJS_BOOTPACK = bootpack.c nasmfunc.o hankaku.o mysprintf.o graphic.o dsctbl.o
#bootpack.hrb : $(OBJS_BOOTPACK) har.ld
#	$(CC) -m32 -march=i486 -nostdlib -nostdinc -T har.ld $(OBJS_BOOTPACK) -o $@
#   ここ面倒
OBJS_BOOTPACK = bootpack.o nasmfunc.o hankaku.o graphic.o dsctbl.o int.o fifo.o mysprintf.o mouse.o keyboard.o memory.o sheet.o
bootpack.hrb : $(OBJS_BOOTPACK) har.ld
	ld -m elf_i386 -T har.ld $(OBJS_BOOTPACK) -o $@

haribote.sys : asmhead.bin bootpack.hrb Makefile
	cat asmhead.bin bootpack.hrb > haribote.sys

haribote.img : ipl10.bin haribote.sys Makefile
	mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
	mcopy haribote.sys -i haribote.img ::

img :
	make haribote.img

run :
	make img
	qemu-system-i386 -fda haribote.img	# "-fda" for floppy disk

debug:
	make img
	qemu-system-i386 -fda haribote.img -gdb tcp::10000 -S

clean :
	rm *.o
	rm *.lst
	rm *.bin
	rm *.hrb
	rm *.sys

src_only :
	rm haribote.img
	make clean


