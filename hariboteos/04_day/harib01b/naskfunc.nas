; naskfunc
; TAB=4

[FORMAT "WCOFF"]        ; ����Ŀ���ļ���ģʽ
[INSTRSET "i486p"]       ;����nask���������486�Ļ�������
[BITS 32]			    ; ����32λģʽ�Ļ�������			
[FILE "naskfunc.nas"]			

		GLOBAL	_io_hlt,_write_mem8

[SECTION .text]	

_io_hlt:	
		HLT
		RET

_write_mem8:        ; write_mem8(int addr, int data)

        MOV     ECX,[ESP+4]
        MOV     AL,[ESP+8]
        MOV     [ECX],AL
        RET
