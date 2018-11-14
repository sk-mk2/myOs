## C言語と画面表示の練習
C言語から自由に使えるレジスタはEAX,ECX,EDX
char *p //これはpという変数がメモリ番地専用変数という意味
アセンブリとの型の対応
C：アセンブリ
char：BYTE
short：WORD
int：DWORD

なんでこれで表示されるのかよくわからんな
どこでVRAM使ってんだ？

そういえば明示的にキャストしないと怒られたわ
ポインタすこしアセンブラの気持ちになるとわかりやすい
char* p,q これはpだけしか番地を表す変数にならない
配列もポインタの意味がわかった気がする
p[i] は*(p+i)
つまりi[p]は*(i+p)
RESBの代わりにDB命令を使うのが変数宣言の時にstaticをつける
signed char:-128 ~ 127
unsigned char:0 ~ 255
もちろんCPUはメモリとしか繋がっていないわけではなく、
キーボートやLANカードなどの他のデバイスとつながっている
Cからはつなぐ命令が無いので、装置番号を調べる
http://community.osdev.info/?VGA

interrupt flag
CLI:clear interrupt flag
STI:set interrupt flag
キャリーフラグとかと同列のフラグ類
制御でCPUの割り込みを制御することができる

EFLAGSというフラグが詰まった32bitレジスタがあり、そこでCPUの制御に関するフラグを設定できる

アセンブリではRETした時にEAXレジスタに入っていた値が関数の値とみなされる

今の画面モードでは320*200画素
(x,y)を表すVRAMの番地は
0xa0000 + x + y * 320

