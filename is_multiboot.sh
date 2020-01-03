#!/bin/bash

set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "Expected 1 arguments but got $#"
  echo "Usage: is_multiboot <bin_file_name>"
  exit 1
fi

GRUB_PREFIX=$(brew --prefix i386-elf-grub)
BIN_TO_CHECK=$1

if "$GRUB_PREFIX"/bin/i386-elf-grub-file --is-x86-multiboot "$BIN_TO_CHECK"; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
