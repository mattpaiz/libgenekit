IDIR        := .
BINFILE     := symreg 
CC          := gcc
CFLAGS      := -Wall -lgenekit
LIB         := ../../lib
INCLUDE     := ../../include

FILES       := $(wildcard *.c) 

OSNAME      := $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
ISLINUX     := $(strip $(findstring LINUX, $(OSNAME)))

ifneq ($(LINUX),)
  CFLAGS += -lm
endif

symreg : $(FILES) 
	$(CC) -o $(BINFILE) $(FILES) $(CFLAGS) -I$(INCLUDE) -L$(LIB)

clean: 
	rm $(BINFILE)

