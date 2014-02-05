.PHONY: all install clean rapport

all:
	$(MAKE) -C libmatrice -f Makefile.$(MAKESUFFIX)
	$(MAKE) -C libmatrice -f Makefile.$(MAKESUFFIX) install
	$(MAKE) -C GO -f Makefile.$(MAKESUFFIX)

install:
	$(MAKE) -C GO -f Makefile.$(MAKESUFFIX) install

clean:
	$(MAKE) -C libmatrice -f Makefile.$(MAKESUFFIX) clean
	$(MAKE) -C GO -f Makefile.$(MAKESUFFIX) clean

rapport:
	$(MAKE) -C rapport

archive: clean rapport
	mkdir ProjetGo-dist

	cp Makefile.* ProjetGo-dist/
	cp README.md ProjetGo-dist/

	cp -r doc ProjetGo-dist/
	rm -f ProjetGo-dist/doc/Doxyfile-*
	rm -f ProjetGo-dist/doc/empty

	cp -r rapport ProjetGo-dist/
	rm -f ProjetGo-dist/rapport/.project

	mkdir ProjetGo-dist/libmatrice
	mkdir ProjetGo-dist/libmatrice/bin
	cp -r libmatrice/src ProjetGo-dist/libmatrice
	cp libmatrice/Makefile.* ProjetGo-dist/libmatrice

	mkdir ProjetGo-dist/GO
	mkdir ProjetGo-dist/GO/bin
	mkdir ProjetGo-dist/GO/include
	mkdir ProjetGo-dist/GO/obj

	cp GO/Makefile.* ProjetGo-dist/GO/

	cp -r GO/assets ProjetGo-dist/GO
	cp -r GO/include/SDL ProjetGo-dist/GO/include
	cp -r GO/installlibs ProjetGo-dist/GO
	cp -r GO/lib ProjetGo-dist/GO
	cp -r GO/src ProjetGo-dist/GO

	rm -f ProjetGo-dist/GO/lib/libmatrice.*

	tar -cf ProjetGo.tar ProjetGo-dist
	gzip ProjetGo.tar

	rm -rf ProjetGo-dist
	