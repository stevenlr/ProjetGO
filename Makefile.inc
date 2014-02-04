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
	