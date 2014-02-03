FICHIERS=$(wildcard *.md)
OUTPDF=rapport.pdf

all:
	cat $(FICHIERS) > tmp
	iconv -t utf-8 tmp > tmp2
	pandoc tmp2 -s -N --toc --toc-depth=2 -o $(OUTPDF)
	rm tmp tmp2