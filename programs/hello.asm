[BITS 32]

mov dl, 0x4c        
mov al, 'H'
mov byte [0xB8000], al
mov byte [0xB8001], dl

mov al, 'E'
mov byte [0xB8002], al
mov byte [0xB8003], dl

mov al, 'L'
mov byte [0xB8004], al
mov byte [0xB8005], dl

mov al, 'L'
mov byte [0xB8006], al
mov byte [0xB8007], dl

mov al, '0'
mov byte [0xB8008], al
mov byte [0xB8009], dl

ret


