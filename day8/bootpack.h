
// bootpack.h


// stdio
void sprintf(char *str, char *fmt, ...);

// asmhead.asm
struct BootInfo {   // 1x5+2x2 = 9 byte
  char cyls;        // ブートセクタはどこまでディスクを読み込んだのか
  char leds;        // ブート時のキーボードのLED状態
  char vmode;       // ビデオモード 何ビットカラーか
  char reserve;
  short scrnx, scrny;   // 画像解像度
  char *vram;
};
#define ADR_BOOTINFO  0x00000ff0


// nasmfunc.c
void io_hlt(void);
void io_cli(void);
void io_sti(void);
void io_stihlt(void);
int io_in8(int port);
void io_out8(int port, int data);
int  io_load_eflags(void);
void io_store_eflags(int eflags);
void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);
void asm_inthandler21(void);
void asm_inthandler27(void);
void asm_inthandler2c(void);


// graphic.c
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void init_screen8(char *vram, int x, int y);
void putfont8(char *vram, int xsize, int x, int y, char c, char *font);
void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s);
void init_mouse_cursor8(char *mouse, char bc);
void putblock8_8(char *vram,int vxsize,int pxsize,int pysize,int px0,int py0,char *buf, int bxsize);
#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15


// dsctbl.c
struct SegmentDescriptor {            // 8 byte
  short limit_low, base_low;          // 2 byte * 2
  char base_mid, access_right;        // 1 byte * 2
  char limit_high, base_high;         // 1 byte * 2
};

struct GateDescriptor {               // 10 byte   
  short offset_low, selector;         // 2 byte * 2
	char dw_count, access_right;        // 1 byte * 2
	short offset_high;                  // 2 byte * 2
};
void set_segmdesc(struct SegmentDescriptor * sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GateDescriptor * gd, int offset, int selector, int ar);
void init_gdtidt(void);
#define ADR_IDT     0x0026f800    // 4 byte
#define LIMIT_IDT   0x000007ff    // 4 byte
#define ADR_GDT     0x00270000    // 4 byte
#define LIMIT_GDT   0x0000ffff    // 4 byte
#define ADR_BOTPAK  0x00280000    // 4 byte
#define LIMIT_BOTPAK  0x0007ffff  // 4 byte
#define AR_DATA32_RW  0x4092      // 2 byte
#define AR_CODE32_ER  0x409a      // 2 byte
#define AR_INTGATE32  0x008e      // 2 byte


// int.c
void init_pic(void);
void inthandler21(int *esp);
void inthandler27(int *esp);
void inthandler2c(int *esp);
#define PIC0_ICW1 0x0020
#define PIC0_OCW2 0x0020
#define PIC0_IMR  0x0021
#define PIC0_ICW2 0x0021
#define PIC0_ICW3 0x0021
#define PIC0_ICW4 0x0021
#define PIC1_ICW1 0x00a0
#define PIC1_OCW2 0x00a0
#define PIC1_IMR  0x00a1
#define PIC1_ICW2 0x00a1
#define PIC1_ICW3 0x00a1
#define PIC1_ICW4 0x00a1
  // PICはポート番号が同じでも区別してくれる

//fifo
struct FIFO8 {
    unsigned char *buf;
    int p, q, size, free, flags;
};

void fifo8_init(struct FIFO8 *fifo, int size, unsigned char *buf);
int fifo8_put(struct FIFO8 *fifo, unsigned char data);
int fifo8_get(struct FIFO8 *fifo);
int fifo8_status(struct FIFO8 *fifo);



