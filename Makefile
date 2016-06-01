MAKE = make
DISTDIR = ./build

all: lib sh module generate

lib:
	cd ./lib
	$(MAKE)

sh: lib
	cd ./sh
	$(MAKE)

module: 
	cd ./module
	$(MAKE)

generate: lib sh module
	mkdir -p $(DISTDIR)/bin
	cp ./sh/*.tns $(DISTDIR)/
	cp ./module/*/*.tns $(DISTDIR)/bin/
	cp ./template/*.tns $(DISTDIR)/

clean: clean-generate clean-module clean-sh clean-lib

clean-lib:
	cd ./lib
	$(MAKE) clean

clean-sh: 
	cd ./sh
	$(MAKE) clean

clean-module: 
	cd ./module
	$(MAKE) clean

clean-generate:
	rm -f $(DISTDIR)/*.tns
	