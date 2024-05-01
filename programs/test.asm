; Disassembly of file: programs/test.o
; Wed May  1 08:37:46 2024
; Mode: 64 bits
; Syntax: YASM/NASM
; Instruction set: 8086, x64

default rel

global main: function


SECTION .text   align=1 execute                         ; section number 1, code

main:   ; Function begin
        endbr64                                         ; 0000 _ F3: 0F 1E. FA
        push    rbp                                     ; 0004 _ 55
        mov     rbp, rsp                                ; 0005 _ 48: 89. E5
        mov     dword [rbp-0CH], 3                      ; 0008 _ C7. 45, F4, 00000003
        mov     dword [rbp-8H], 0                       ; 000F _ C7. 45, F8, 00000000
        jmp     ?_002                                   ; 0016 _ EB, 0A

?_001:  mov     eax, dword [rbp-8H]                     ; 0018 _ 8B. 45, F8
        add     dword [rbp-0CH], eax                    ; 001B _ 01. 45, F4
        add     dword [rbp-8H], 1                       ; 001E _ 83. 45, F8, 01
?_002:  cmp     dword [rbp-8H], 499                     ; 0022 _ 81. 7D, F8, 000001F3
        jle     ?_001                                   ; 0029 _ 7E, ED
        mov     dword [rbp-4H], 1                       ; 002B _ C7. 45, FC, 00000001
; Note: Address is not rip-relative
; Note: Absolute memory address without relocation
        mov     dl, byte [abs 4CH]                      ; 0032 _ 8A. 14 25, 0000004C
        mov     al, 72                                  ; 0039 _ B0, 48
; Note: Address is not rip-relative
; Note: Absolute memory address without relocation
        mov     byte [abs 0B8000H], al                  ; 003B _ 88. 04 25, 000B8000
; Note: Address is not rip-relative
; Note: Absolute memory address without relocation
        mov     byte [abs 0B8001H], dl                  ; 0042 _ 88. 14 25, 000B8001
        mov     eax, 0                                  ; 0049 _ B8, 00000000
        pop     rbp                                     ; 004E _ 5D
        ret                                             ; 004F _ C3
; main End of function


SECTION .data   align=1 noexecute                       ; section number 2, data


SECTION .bss    align=1 noexecute                       ; section number 3, bss


SECTION .note.gnu.property align=8 noexecute            ; section number 4, const

        db 04H, 00H, 00H, 00H, 10H, 00H, 00H, 00H       ; 0000 _ ........
        db 05H, 00H, 00H, 00H, 47H, 4EH, 55H, 00H       ; 0008 _ ....GNU.
        db 02H, 00H, 00H, 0C0H, 04H, 00H, 00H, 00H      ; 0010 _ ........
        db 03H, 00H, 00H, 00H, 00H, 00H, 00H, 00H       ; 0018 _ ........


