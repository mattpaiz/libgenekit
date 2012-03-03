IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -g	-Wall

BINDIR=../build
LIBDIR=../lib

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = function.o tree.o equation.o chromosome.o mutate.o simulation.o kernel.o
OBJ = $(patsubst %,$(BINDIR)/%,$(_OBJ))

$(BINDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIBDIR)/libgenekit.a: $(OBJ)
	ar rcs $@ $^

install: $(LIBDIR)/libgenekit.a
	cp $(LIBDIR)/libgenekit.a /usr/local/lib/		
	cp genekit.h /usr/local/include/		
	cp rand.h kernel.h simulation.h function.h tree.h equation.h chromosome.h mutate.h /usr/local/include/genekit/

clean: 
	rm $(BINDIR)/*.o $(LIBDIR)/*.a

