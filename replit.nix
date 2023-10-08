{ pkgs }: {
    deps = [
        pkgs.minio-client
        pkgs.gnome.ghex
        pkgs.qemu
        pkgs.cdrtools
        pkgs.nasm
    ];
}