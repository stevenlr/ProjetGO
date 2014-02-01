OBJDIR=$(BASEDIR)/obj

CC=gcc
CFLAGS=-Wall -O3 -I$(BASEDIR)/include -I$(BASEDIR)/src

SRC=$(wildcard *.c)
OBJ=$(addprefix $(OBJDIR)/$(OBJPREFIX),$(patsubst %.c, %.o, $(SRC)))

.PHONY: all clean clean_inc

compile: depend.d $(OBJ)

depend.d: $(SRC)
	$(CC) $^ -MM -E -I$(BASEDIR)/src >> $@

include depend.d

$(OBJDIR)/$(OBJPREFIX)%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean_inc:
	rm depend.d