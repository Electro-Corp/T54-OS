rm -d -r -f out
mkdir out
cp t54.iso t54_OLD.iso
rm t54.iso
nasm -f elf src/boot.asm -o out/boot.o

echo Comp C Source
gcc -c  src/main.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/main.o
gcc -c  src/vga.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/vga.o
gcc -c  src/fs.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/fs.o
gcc -c  src/cd.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/cd.o
gcc -c  src/io.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/io.o

ld -T link.ld -melf_i386 out/boot.o out/fs.o out/main.o out/vga.o out/cd.o out/io.o -o iso/boot/kernel

echo Comp Programs
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
qemu-system-x86_64 -drive file=t54.iso,if=ide,media=cdrom -hdd test.img
