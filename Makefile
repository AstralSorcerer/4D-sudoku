SHELL=/bin/sh
BUILDDIR=build
SRCDIR=src
CC=gcc
LFLAGS=-lGL -lX11

all : sudoku

sudoku : $(SRCDIR)/main.o $(SRCDIR)/xutil.o $(SRCDIR)/event_callbacks.o $(SRCDIR)/draw.o
	test -d $(BUILDDIR) || mkdir $(BUILDDIR)
	$(CC) -o $(BUILDDIR)/$@ $^ $(LFLAGS)
clean :
	rm $(BUILDDIR)/* $(SRCDIR)/*.o
