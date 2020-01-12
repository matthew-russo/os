#!/bin/sh

set -e

PATH=$(brew --prefix qemu)/bin:$PATH

. ./iso.sh
 
qemu-system-$(./target-triplet-to-arch.sh $HOST) \
  -serial mon:stdio  \
  -cdrom myos.iso
