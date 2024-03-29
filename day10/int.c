
// int.c

#include "bootpack.h"

void init_pic(void)
{
  // interupt mask register
  io_out8(PIC0_IMR, 0xff);    // すべての割り込みを受け付けない
  io_out8(PIC1_IMR, 0xff);    // すべての割り込みを受け付けない

  // initial control word
  io_out8(PIC0_ICW1, 0x11);   // 固定 : エッジトリガモード
  io_out8(PIC0_ICW2, 0x20);   // IRQ0-7はINT20-27で受ける
  io_out8(PIC0_ICW3, 1 << 2); // PIC1はPIC2に接続
  io_out8(PIC0_ICW4, 0x01);   // 固定 : ノンバッファモード

  io_out8(PIC1_ICW1, 0x11);   // 固定 : エッジトリガモード
  io_out8(PIC1_ICW2, 0x28);   // IRQ0-7はINT20-27で受ける
  io_out8(PIC1_ICW3, 2);      // PIC1はPIC2に接続
  io_out8(PIC1_ICW4, 0x01);   // 固定 : ノンバッファモード

  io_out8(PIC0_IMR, 0xfb);    // 11111011 PIC1以外はすべて禁止
  io_out8(PIC1_IMR, 0xff);    // 11111111 すべての割り込みを受け付けない
}


void inthandler27(int *esp)
{
	io_out8(PIC0_OCW2, 0x67); 
	return;
}
