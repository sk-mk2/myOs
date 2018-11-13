# ファイル生成規則

ipl.bin : ipl.asm Makefile
	nasm ipl.asm -o ipl.bin -l ipl.lst

helloos.img : ipl.bin Makefile
	cat ipl.bin > helloos.img

asm :
	make -r ipl.bin

img :
	make -r helloos.img

run :
	make img
	qemu-system-i386 helloos.img

clean :
	rm ipl.bin helloos.img ipl.lst



