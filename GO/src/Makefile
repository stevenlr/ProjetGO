BASEDIR=..
OBJPREFIX=

all: compile
	$(MAKE) -C graphics
	$(MAKE) -C modes

clean: clean_inc
	$(MAKE) -C graphics clean
	$(MAKE) -C modes clean

include Makefile.inc