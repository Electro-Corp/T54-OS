[BITS 32]

mov dl, 0x4c

; Write H   
mov al, 'H'
mov byte [0xB8000], al
mov byte [0xB8001], dl


extern _kprintf
goof db "hello world"
push goof
call _kprintf
ret