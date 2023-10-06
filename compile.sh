rm -d -r -f out
mkdir out
cp t54.iso t54_OLD.iso
rm t54.iso
nasm -f elf boot.asm -o out/boot.o

echo Comp C Source
gcc -c  main.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/main.o
gcc -c  vga.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/vga.o
gcc -c  fs.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/fs.o
gcc -c  cd.c -m32 -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -W -o out/cd.o


#ld -T link.ld -melf_i386 out/main.o -Ttext 0x0 out/boot.o out/vga.o out/fs.o -o iso/boot/kernel
ld -T link.ld -melf_i386 out/boot.o out/fs.o out/main.o out/vga.o out/cd.o -o iso/boot/kernel
# mkisofs -R                                   \
#                -b grub/stage2_eltorito    \
#                -no-emul-boot                   \
#                -boot-load-size 4               \
#                -A T54                           \
#                -input-charset utf8             \
#                -quiet                          \
#                -boot-info-table                \
#                -o t54.iso                       \
#                boot
mkisofs -R                              \
                -b  boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o t54.iso                       \
                iso
qemu-system-x86_64 -cdrom t54.iso