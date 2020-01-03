#!/bin/bash

set -euo pipefail

if [ "$#" -ne 3 ]; then
  echo "Expected 3 arguments but got $#"
  echo "Usage: make_iso <bin_file_name> <grub_cfg_file_name> <output_iso_file_name>"
  exit 1
fi

GRUB_PREFIX=$(brew --prefix i386-elf-grub)
BIN_FILE=$1
GRUB_CFG=$2
OUTPUT_FILE=$3

mkdir -p isodir/boot/grub
cp "$BIN_FILE" isodir/boot/myos.bin
cp "$GRUB_CFG" isodir/boot/grub/grub.cfg
"$GRUB_PREFIX"/bin/i386-elf-grub-mkrescue -o "$OUTPUT_FILE" isodir
rm -rf isodir
