MODULEDIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d)
BUILDMODULES = $(addprefix __build__, $(MODULEDIRS))
CLEANMODULES = $(addprefix __clean__, $(MODULEDIRS))

TEMPLATE_DIR = ../template
NAME = 

MAKE = make

all: $(BUILDMODULES)

clean: $(CLEANMODULES)

$(BUILDMODULES):
	$(MAKE) -C $(patsubst __build__%,%,$@)

$(CLEANMODULES):
	$(MAKE) -C $(patsubst __clean__%,%,$@) clean

new:
ifeq ($(NAME),)
	@echo ""
	@echo "Usage: make new NAME=<module name>"
	@echo ""
	@false
endif
	mkdir -p ./$(NAME)
	cp $(TEMPLATE_DIR)/module/main.c.tpl ./$(NAME)/main.c
	sed -e "s/@@EXENAME@@/$(NAME)/" "$(TEMPLATE_DIR)/module/Makefile.tpl" > ./$(NAME)/Makefile
