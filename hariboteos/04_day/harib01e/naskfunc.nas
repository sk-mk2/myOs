; naskfunc
; TAB=4

[FORMAT "WCOFF"]        ; ����Ŀ���ļ���ģʽ
[INSTRSET "i486p"]       ;����nask���������486�Ļ�������
[BITS 32]			    ; ����32λģʽ�Ļ�������			
[FILE "naskfunc.nas"]			

		GLOBAL	_io_hlt

[SECTION .text]	

_io_hlt:	
		HLT
		RET

