#!/bin/bash

PREFIX="$HOME/opt/cross"
TARGET=i686-elf
PATH="$PREFIX/bin:$PATH"

git clone https://github.com/gcc-mirror/gcc.git
git clone https://github.com/bminor/binutils-gdb.git

mkdir build-binutils
cd build-binutils
../binutils-gdb/configure \
  --prefix=$PREFIX \
  --target=$TARGET \
  --enable-interwork \
  --enable-multilib \
  --with-sysroot \
  --disable-nls \
  --disable-werror
make
make install

cd ..
 
# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH
 
mkdir build-gcc
cd build-gcc
../gcc/configure \
  --prefix=$PREFIX \
  --target=$TARGET \
  --disable-nls \
  --enable-languages=c,c++ \
  --without-headers \
  --enable-interwork \
  --enable-multilib \
  --with-gmp=/usr \
  --with-mpc=/opt/local \
  --with-mpfr=/opt/local \
  --with-libiconv-prefix=/opt/local
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

