mov dl, [1]
mov al, 'A'
mov byte [0xB8000 + ebx], al
mov byte [0xB8001 + ebx], dl