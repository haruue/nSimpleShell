MAKE = make
DISTDIR = ./build

all: generate

lib:
	$(MAKE) -C ./lib

sh: lib
	$(MAKE) -C ./sh

module: 
	$(MAKE) -C ./module

generate: sh module
	mkdir -p $(DISTDIR)/bin
	find ./sh/ -name "*\.tns" -exec cp {} $(DISTDIR)/ \;
	find ./module/ -name "*\.tns" -exec cp {} $(DISTDIR)/bin/ \;
	find ./template/ -name "*\.tns" -exec cp {} $(DISTDIR)/ \;

clean: clean-generate clean-module clean-sh clean-lib

clean-lib:
	$(MAKE) -C ./lib clean

clean-sh: 
	$(MAKE) -C ./sh clean

clean-module: 
	$(MAKE) -C ./module clean

clean-generate:
	rm -f $(DISTDIR)/*.tns
	rm -f $(DISTDIR)/bin/*.tns
	
.PHONY: lib sh module generate clean clean-lib clean-sh clean-module clean-generate