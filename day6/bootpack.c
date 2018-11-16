// bootpack.c
//headerファイルに書き込めばこれで読み込める
#include "bootpack.h"
//externは外部ファイルから読み込むとき
//--------------------
//  HariMain
//--------------------
void HariMain(void)
{
  struct BootInfo *binfo = (struct BootInfo *) 0x0ff0;
  extern char hankaku[4096];
  char s[40], mcursor[256];
  int mx, my;   // mouse x, mouse y
  
  init_gdtidt();
  init_pic();
  io_sti(); 

  init_palette();
  init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);

  putfonts8_asc(binfo->vram, binfo->scrnx,  8,  8, COL8_FFFFFF, "ABC 123");
  putfonts8_asc(binfo->vram, binfo->scrnx, 31, 31, COL8_000000, "Haribote OS");
  putfonts8_asc(binfo->vram, binfo->scrnx, 30, 30, COL8_FFFFFF, "Haribote OS");

  mx = (binfo->scrnx - 16) / 2;
  my = (binfo->scrny - 28 - 16) / 2;

  init_mouse_cursor8(mcursor, COL8_008484);
  putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

  sprintf(s, "scrnx = %d", binfo->scrnx);
  putfonts8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);
  io_out8(PIC0_IMR, 0xf9); 
  io_out8(PIC1_IMR, 0xef);

  for(;;){
    io_hlt();
  }
}


