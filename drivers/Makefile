DEFAULT_HOST=$(shell ../default-host.sh)
HOST?=$(DEFAULT_HOST)
HOSTARCH=$(shell ../target-triplet-to-arch.sh $(HOST))
 
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -Iinclude
 
ARCHDIR=arch/$(HOSTARCH)
 
include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

DRIVERS_OBJS=\
$(DRIVERS_ARCH_OBJS) \

OBJS=\
$(DRIVERS_OBJS) \

BINARIES=libdrivers.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .c .S

all: $(BINARIES)

libdrivers.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-drivers

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R -p include/. $(DESTDIR)$(INCLUDEDIR)/.

install-drivers: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)/$(LIBDIR)

-include $(OBJS:.o=.d)

