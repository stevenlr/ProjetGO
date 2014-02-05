FICHIERS=$(wildcard *.md)
OUTPDF=rapport.pdf

all:
	cat $(FICHIERS) > tmp
	pandoc tmp -s -N --toc --toc-depth=2 -o $(OUTPDF)
	rm tmp