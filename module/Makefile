MODULEDIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d)

TEMPLATE_DIR = ../template

MAKE = make

all:
	@for i in $(MODULEDIRS); do \
	echo "make all in $$i..."; \
	(cd $$i; $(MAKE) all) || exit 1; done
  
clean:
	@for i in $(MODULEDIRS); do \
	echo "Clearing in $$i..."; \
	(cd $$i; $(MAKE) clean) || exit 1; done

.PHONY: help, new

help:
	@echo ""
	@echo "Usage: make all - build all modules"
	@echo "       make clean - clean all modules"
	@echo "       make new NAME=<module name> - create a new module named <module name>"

new:
ifeq ($(NAME),)
	@echo ""
	@echo "Usage: make new NAME=<module name> - create a new module named <module name>"
else
	mkdir -p ./$(NAME)
	cp $(TEMPLATE_DIR)/module/main.c.tpl ./$(NAME)/main.c
	sed -e "s/@@EXENAME@@/$(NAME)/" "$(TEMPLATE_DIR)/module/Makefile.tpl" > ./$(NAME)/Makefile
endif
