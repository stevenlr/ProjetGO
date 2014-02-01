CC=gcc
CFLAGS=-Wall -O3
LDFLAGS=-shared -fPIC

.PHONY: all

all: $(BIN)
	mv $(BIN) bin

$(BIN): src/matrice.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
	
clean:

install:
	cp bin/$(BIN) ../GO/lib
	cp bin/$(BIN) ../GO/bin
	cp src/include/matrice.h ../GO/include/