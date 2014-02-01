CC=gcc
CFLAGS=-O3
LDFLAGS=-shared -fPIC

.PHONY: all

all: $(BIN)
	mv $(BIN) bin

$(BIN): src/matrice.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
	
clean:

install:
	mkdir -p ../GO/lib
	mkdir -p ../GO/bin
	cp bin/$(BIN) ../GO/lib
	cp bin/$(BIN) ../GO/bin
	mkdir -p ../GO/include
	cp src/include/matrice.h ../GO/include/
