global entry
section .__mbHeader

align 0x4
MAGIC equ 0x1BADB002 ; These tell the bootloader that we are bootable
FLAGS equ 0
SUM equ -MAGIC

section .text
align 4 ; Align everything after this to a 4 byte boundary, which the boot header needs to be aligned to
        dd MAGIC ; dd means "define double word", a word is usually 2 bytes on most computers, so a dword is 4 bytes. You can think of a word as being a short in C and a dword being an int.
        dd FLAGS
        dd SUM

CSTACK_SIZE equ 80000 ; This is how big we want our stack to be

entry:
mov esp, cstack + CSTACK_SIZE ; The ESP register holds the current position on the stack

extern kmain
call kmain

jmp entry ; if main returns, just do nothing. there isn't anything else to do here

section .bss:
    
align 16 ; We should align our stack on a 4 byte boundary, im unsure of the consquences of not doing this but im sure you do not want to find out.
cstack:
resb CSTACK_SIZE ; resb == "reserve bytes"
