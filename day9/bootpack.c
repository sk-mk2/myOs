// bootpack.c
//headerファイルに書き込めばこれで読み込める
#include "bootpack.h"
//#include <stdio.h>

//externは外部ファイルから読み込むとき
//--------------------
//  HariMain
//--------------------

void HariMain(void)
{
  struct BootInfo *binfo = (struct BootInfo *) 0x0ff0;
  extern char hankaku[4096];
  char s[40], mcursor[256], keybuf[32], mousebuf[128];
  int mx, my, i;   // mouse x, mouse y
  struct MOUSE_DEC mdec;
  
  init_gdtidt();
  init_pic();
  io_sti();
  fifo8_init(&keyfifo, 32, keybuf);
  fifo8_init(&mousefifo, 128, mousebuf);
  io_out8(PIC0_IMR, 0xf9); 
  io_out8(PIC1_IMR, 0xef);
  
  init_keyboard();

  init_palette();
  init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
  /*
  putfonts8_asc(binfo->vram, binfo->scrnx,  8,  8, COL8_FFFFFF, "ABC 123");
  putfonts8_asc(binfo->vram, binfo->scrnx, 31, 31, COL8_000000, "Haribote OS");
  putfonts8_asc(binfo->vram, binfo->scrnx, 30, 30, COL8_FFFFFF, "Haribote OS");
  */

  mx = (binfo->scrnx - 16) / 2;
  my = (binfo->scrny - 28 - 16) / 2;
  init_mouse_cursor8(mcursor, COL8_008484);
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
  sprintf(s, "(%d, %d)", mx, my);
  putfonts8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

  enable_mouse(&mdec);

  for(;;){
    io_cli();
    if (fifo8_status(&keyfifo) + fifo8_status(&mousefifo) == 0) {
        io_stihlt();
    } else {
        if (fifo8_status(&keyfifo) != 0) {
            i = fifo8_get(&keyfifo);
            io_sti();
            sprintf(s, "%x", i);
            boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
            putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);

        } else if (fifo8_status(&mousefifo) != 0){
            i = fifo8_get(&mousefifo);
            io_sti();
            if (mouse_decode(&mdec, i) != 0) {
                sprintf(s, "[lcr %x %x]", mdec.x, mdec.y);
                if ((mdec.btn & 0x01) != 0) {
                    s[1] = 'L';
                }
                if ((mdec.btn & 0x02) != 0) {
                    s[3] = 'R';
                }
                if ((mdec.btn & 0x04) != 0) {
                    s[2] = 'C';
                }
                boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 32 + 15 * 8 - 1, 31);
                putfonts8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);
                boxfill8(binfo->vram, binfo->scrnx, COL8_008484, mx, my, mx + 15, my + 15); 
                mx += mdec.x;
                my += mdec.y;
                if (mx < 0) {
                    mx = 0;
                }
                if (my < 0) {
                    my = 0;
                }
                if (mx > binfo->scrnx - 16) {
                    mx = binfo->scrnx - 16;
                }
                if (my > binfo->scrny - 16) {
                    my = binfo->scrny - 16;
                }
                sprintf(s, "(%3d, %3d)", mx, my);
                boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 0, 79, 15); 
                putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s); 
                putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16); 
            }
        }
    }
  }
}
