BASEDIR=.
BINDIR=$(BASEDIR)/bin
OBJDIR=$(BASEDIR)/obj

CC=gcc
LDFLAGS=-L$(BASEDIR)/lib $(LIBS) -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lmatrice

.PHONY: all clean install installgeneric installplatformdependent

all:
	$(MAKE) -C src
	$(CC) $(OBJDIR)/*.o -o $(BINDIR)/$(BIN) $(LDFLAGS)

install: installgeneric installplatformdependent

installgeneric:
	cp -R assets $(BINDIR)
	rm $(BINDIR)/assets/Tutoriel.txt

clean:
	$(MAKE) -C src clean
	rm -f $(OBJDIR)/*.o