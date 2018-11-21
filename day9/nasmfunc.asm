; nasmfunc.asm
; TAB=4

;write_mem8: ; void write_mem8(int addr, int data)
;    MOV ECX, [ESP+4] ;[ESP+4]にaddrが入っているのでそれをECXに読み込む
;    MOV AL, [ESP+8]  ;[ESP+8]にdataが入っている
;    MOV [ECX], AL
;    RET
section .text
        GLOBAL  io_hlt, io_cli, io_sti, io_stihlt
        global  io_in8, io_in16, io_in32
        global  io_out8, io_out16, io_out32
        global  io_load_eflags, io_store_eflags
        global  load_gdtr, load_idtr
		GLOBAL	asm_inthandler21, asm_inthandler27, asm_inthandler2c
		GLOBAL	load_cr0, store_cr0
		EXTERN	inthandler21, inthandler27, inthandler2c


io_hlt:             ; void io_hlt(void);
        HLT
        RET

io_cli:     ; void io_cli(void);
        cli
        ret

io_sti:     ; void io_sti(void);
        sti
        ret

io_stihlt:      ; void io_stihlt(void);
        sti
        hlt
        ret

io_in8:     ; int io_in8(int port);
        mov     edx, [esp + 4]      ; port
        mov     eax, 0
        in      al, dx              ; 8
        ret

io_in16:        ; int io_in16(int port);
        mov     edx, [esp + 4]      ; port
        mov     eax, 0
        in      ax, dx              ; 16
        ret

in_in32:        ; int io_in16(int port);
        mov     edx, [esp + 4]      ; port
        in      eax, dx             ; 32
        ret

io_out8:        ; void io_to_in_out8;
        mov     edx, [esp + 4]      ; port
        mov     al, [esp + 8]       ; data
        out     dx, al              ; 8
        ret

io_out16:       ; void io_to_in_out16;
        mov     edx, [esp + 4]      ; port
        mov     eax, [esp + 8]      ; data
        out     dx, ax              ; 16
        ret

io_out32:       ; void io_to_in_out32;
        mov     edx, [esp + 4]      ; port
        mov     eax, [esp + 8]      ; data
        out     dx, eax             ; 32
        ret

io_load_eflags:     ; int io_load_eflags(void);
        pushfd      ; push eflags double-word
        pop     eax
        ret

io_store_eflags:        ; void io_store_eflags(int eflags);
        mov     eax, [esp + 4]
        push    eax
        popfd       ; pup eflags double-word
        ret

load_gdtr:        ; void load_gdtr(int limit, int addr)
        mov     ax, [esp + 4]       ; limit
        mov     [esp + 6], ax
        lgdt    [esp + 6]
        ret
 
load_idtr:        ; void load_idtr(int limit, int addr)
        mov     ax, [esp + 4]       ; limit
        mov     [esp + 6], ax
        lidt    [esp + 6]
        ret


asm_inthandler21:
		PUSH	ES
		PUSH	DS
		PUSHAD
		MOV		EAX,ESP
		PUSH	EAX
		MOV		AX,SS
		MOV		DS,AX
		MOV		ES,AX
		CALL	inthandler21
		POP		EAX
		POPAD
		POP		DS
		POP		ES
		IRETD

asm_inthandler27:
		PUSH	ES
		PUSH	DS
		PUSHAD
		MOV		EAX,ESP
		PUSH	EAX
		MOV		AX,SS
		MOV		DS,AX
		MOV		ES,AX
		CALL	inthandler27
		POP		EAX
		POPAD
		POP		DS
		POP		ES
		IRETD

asm_inthandler2c:
		PUSH	ES
		PUSH	DS
		PUSHAD
		MOV		EAX,ESP
		PUSH	EAX
		MOV		AX,SS
		MOV		DS,AX
		MOV		ES,AX
		CALL	inthandler2c
		POP		EAX
		POPAD
		POP		DS
		POP		ES
		IRETD

load_cr0:
        MOV EAX, CR0
        RET


store_cr0:
        MOV EAX, [ESP+4]
        MOV CR0, EAX
        RET

