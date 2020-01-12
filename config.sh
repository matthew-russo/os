SYSTEM_HEADER_PROJECTS="libc drivers kernel"
PROJECTS="libc drivers kernel"

export PATH=$(pwd)/deps/compiler/run/bin:$PATH
export PATH=$(pwd)/deps/compiler/run/i686-elf/bin/:$PATH
export PATH=$(brew --prefix i386-elf-grub)/bin/:$PATH

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}
 
export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc
 
export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include
 
export CFLAGS='-O2 -g'
export CPPFLAGS=''
 
# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"
 
# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
