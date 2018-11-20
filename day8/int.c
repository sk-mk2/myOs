
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

#define PORT_KEYDAT		0x0060

struct FIFO8 keyfifo;
struct FIFO8 mousefifo;
void inthandler21(int *esp)
{
	unsigned char data;
    io_out8(PIC0_OCW2, 0x61); //IRQ-01受付完了をPICに通知
    data = io_in8(PORT_KEYDAT);
    fifo8_put(&keyfifo, data);

    return;
}

void inthandler2c(int *esp)
{
	unsigned char data;
    //スレーブの奴らはマスタも設定してあげなきゃいけない
    io_out8(PIC1_OCW2, 0x64); //IRQ-12受付完了をPIC1に通知
    io_out8(PIC0_OCW2, 0x62); //IRQ-02受付完了をPIC0に通知
    data = io_in8(PORT_KEYDAT);
    fifo8_put(&mousefifo, data);
    return;
}

void inthandler27(int *esp)
{
	io_out8(PIC0_OCW2, 0x67); 
	return;
}
