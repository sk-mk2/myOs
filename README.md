## 参考サイト
https://github.com/pollenjp/myHariboteOS

## バイナリ編集:
vim -b $file  バイナリモードで開く  
:%!xxd  16進数ダンプ方式に変換  
:%!xxd -r  テキストに戻す 
改行が勝手に入ってしまう
:set binary noeol ファイル末尾の改行コード削除
多分vimをバイナリモードで開いてなかったからかもしれない

## アセンブラ
nasm
nasm *.asm -o *.img

## virtualbox

## 代表的なレジスタ
AX：accumulator
CX：counter
DX：data
BX：base
SP：stack pointer
BP：base pointer
SI：source index
DI：destination index

これらは16bitレジスタ
各種の演算にはAXを使うようにすると機械語が短くなる
それぞれ適した使い方がある

AL,CL,DL,BL,AH,CH,DH,BH
これらは8ビットレジスタ
*Xの16bitレジスタの下位8bitを*L,上位8bitを*H

もちろん32bitレジスタも64bitレジスタもあるこの本では32bitまでしか扱わない
32bitレジスタ
EAX,ECX,EDX,EBX,ESP,EBP,ESI,EDI
Eはextend
このそれぞれの下位16bitが16bitレジスタに対応、上位は無い

## セグメントレジスタ
ES：extra segment
CS：code segment
SS：stack segment
DS：data segment
FS：ななし
GS：ななし


## メモリとレジスタ
MOV BYTE [678],123
メモリ団地の678番地に123を覚えてもらう
MOV WORD [678],123
指定したアドレスと隣、今回だと678,679のアドレスに16bitの数値が入る
下位8bitが678に、上位8bitが679に
DWORDは32bit
アドレスの指定にはレジスタも使えるが限られてる
使える:BX,BP,SI,DI
MOV命令はbit数が同じじゃないとだめ




