; naskfunc
; TAB=4

[FORMAT "WCOFF"]     ; ����Ŀ���ļ���ģʽ
[BITS 32]			 ; ����32λģʽ�Ļ�������			


[FILE "naskfunc.nas"]			
		GLOBAL	_io_hlt			

[SECTION .text]	

_io_hlt:	
		HLT
		RET
