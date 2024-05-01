rm -d -r -f out
mkdir out
cp t54.iso t54_OLD.iso
rm t54.iso
nasm -f elf src/boot.asm -o out/boot.o

echo Comp C Source
gcc -c  src/main.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/main.o
gcc -c  src/vga.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/vga.o
gcc -c  src/fs.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/fs.o
gcc -c  src/cd.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/cd.o
gcc -c  src/term.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/term.o
gcc -c  src/io.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/io.o
gcc -c  src/proc.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/proc.o
gcc -c  src/elf.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/elf.o

gcc -c  src/stdlib.c -m32  -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/stdlib.o


ld -T link.ld -melf_i386 out/boot.o out/fs.o out/main.o out/vga.o out/cd.o out/io.o out/term.o out/proc.o out/elf.o out/stdlib.o -o iso/boot/kernel

echo Comp Programs
rm iso/bin/*
nasm -f bin programs/hello.asm -o iso/bin/hello
nasm -f aout programs/printT.asm -o iso/bin/print

rm programs/test
#gcc -fno-asynchronous-unwind-tables -O0 -s -c -o programs/test.o programs/hello.c
#objcopy -O binary -j .text programs/test.o programs/test
gcc -m32 -c programs/hello.c -o iso/bin/test
cp programs/test iso/bin/test
objconv -fnasm programs/test.o
#nasm -f bin programs/test.asm -o iso/bin/test


gcc -c programs/init.c -o out/init.o
objcopy -O binary -j .text out/init.o iso/bin/init

#gcc programs/init.c -o iso/bin/elf/init
#gcc -Wl,--oformat=a.out-i386-linux programs/init.c -o iso/bin/init 
#gcc -Wl,--oformat=a.out-i386-linux programs/hello.c -o iso/bin/hello

mkisofs -R                              \
                -b  boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o t54.iso                       \
                -V "T54 Root FS"                \
                iso
qemu-system-x86_64 -drive file=t54.iso,if=ide,media=cdrom -hdd test.img #-curses
