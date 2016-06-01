MODULEDIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d)
TEMPLATE_DIR = ../template
NAME = 

MAKE = make

all: $(MODULEDIRS).build

clean: $(MODULEDIRS).clean

$(MODULEDIRS).build:
	$(MAKE) -C $(patsubst %.build,%,$@)

$(MODULEDIRS).clean:
	$(MAKE) -C $(patsubst %.clean,%,$@) clean

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
