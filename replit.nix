{ pkgs }: {
    deps = [
        pkgs.unixtools.util-linux
        pkgs.wget
        pkgs.texinfoInteractive
        pkgs.binutils
        pkgs.minio-client
        pkgs.gnome.ghex
        pkgs.qemu
        pkgs.cdrtools
        pkgs.nasm
    ];
}