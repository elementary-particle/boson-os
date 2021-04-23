#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/boson.kernel isodir/boot/boson.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "boson" {
	multiboot /boot/boson.kernel
}
EOF
$CROSS_PREFIX/bin/grub-mkrescue --install-modules=multiboot -o boson.iso isodir
