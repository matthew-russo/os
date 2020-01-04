#!/bin/bash

TARGET=i686-elf
SCRIPT_PATH="$( cd "$(dirname "$0")" ; pwd -P )"
PREFIX="$SCRIPT_PATH/compiler/run"
PATH="$PREFIX/bin:$PATH"

prep_environment() {
  cd "$PREFIX" || exit
  mkdir -p compiler/build
}

build_binutils() {
  cd "$SCRIPT_PATH" || exit
  cd compiler/build || exit
  git clone https://github.com/bminor/binutils-gdb.git

  mkdir build-binutils
  cd build-binutils || exit
  ../binutils-gdb/configure \
    --prefix="$PREFIX"      \
    --target="$TARGET"      \
    --enable-interwork      \
    --enable-multilib       \
    --with-sysroot          \
    --disable-nls           \
    --disable-werror
  make
  make install
}

validate_binutils() {
  # The $PREFIX/bin dir _must_ be in the PATH. We did that above.
  which -- $TARGET-as || exit 1
}

build_gcc() {
  cd "$SCRIPT_PATH" || exit
  cd compiler/build || exit
  git clone https://github.com/gcc-mirror/gcc.git
  mkdir build-gcc
  cd build-gcc || exit
  ../gcc/configure               \
    --prefix="$PREFIX"           \
    --target=$TARGET             \
    --disable-nls                \
    --enable-languages=c,c++     \
    --without-headers            \
    --enable-interwork           \
    --enable-multilib            \
    --with-gmp=/usr              \
    --with-mpc=/opt/local        \
    --with-mpfr=/opt/local       \
    --with-libiconv-prefix=/opt/local
  make all-gcc
  make all-target-libgcc
  make install-gcc
  make install-target-libgcc
}

prep_environment
build_binutils
validate_binutils
build_gcc
