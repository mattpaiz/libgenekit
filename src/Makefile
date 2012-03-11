IDIR        := .
CC          := gcc
CFLAGS      := -I$(IDIR) -g	-Wall
BINDIR      := ../build
LIBDIR      := ../lib
HEADERDIR   := ../include/genekit
LIBNAME     := libgenekit.a
KERNELDIR   := kernels

INSTALLDEP  := /usr/local/include/genekit
INSTALLLIB  := /usr/local/lib

FILES       := $(wildcard *.c) $(wildcard $(KERNELDIR)/*.c)
DEPS        := $(patsubst %.c,%.h,$(FILES)) rand.h
HEADERS     := $(patsubst %.h,$(HEADERDIR)/%.h,$(DEPS))
OBJS        := $(patsubst %.c,$(BINDIR)/%.o,$(FILES))

OSNAME      := $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
ISLINUX     := $(strip $(findstring LINUX, $(OSNAME)))

ifneq ($(LINUX),)
  CFLAGS += -lm
endif

$(LIBDIR)/$(LIBNAME) : $(OBJS) $(HEADERS)
	ar rcs $@ $^

$(HEADERDIR)/%.h : %.h
	@mkdir -p $(HEADERDIR)
	@mkdir -p $(HEADERDIR)/$(KERNELDIR)
	cp $< $@  

$(BINDIR)/%.o : %.c $(DEPS)
	@mkdir -p $(LIBDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(BINDIR)/$(KERNELDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

install: $(LIBDIR)/$(LIBNAME)
	@mkdir -p $(INSTALLDEP)
	cp $(LIBDIR)/$(LIBNAME) $(INSTALLLIB)
	cp -r $(HEADERDIR)/  $(INSTALLDEP)

clean: 
	rm $(BINDIR)/*.o $(BINDIR)/$(KERNELDIR)/*.o $(LIBDIR)/*.a $(HEADERDIR)/*.h $(HEADERDIR)/$(KERNELDIR)/*.h

