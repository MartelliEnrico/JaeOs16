BASEDIR ?= /usr/local
INCDIR := $(BASEDIR)/include/uarm

CC := arm-none-eabi-gcc
CFLAGS += -O2 -Wall -Wextra
CPPFLAGS += -I $(INCDIR) -I include
TARGET_ARCH := -mcpu=arm7tdmi
LDFLAGS += -T $(INCDIR)/ldscripts/elf32ltsarm.h.uarmcore.x

vpath %.c src
vpath %.c lib/phase1
vpath %.c lib/phase2
vpath %.h $(INCDIR)
vpath %.h include
vpath %.o $(INCDIR)

PROGRAM := build/kernel
common_OBJS := crtso.o libuarm.o
phase1_OBJS := $(subst %.c, %.o, $(wildcard lib/phase1/%.c))
phase1_TEST := p1test.o
phase2_OBJS := $(subst %.c, %.o, $(wildcard lib/phase2/%.c))
phase2_TEST := p2test.o

.PHONY: phase2
phase2: OBJECTS := $(phase1_OBJS) $(phase2_OBJS) $(phase2_TEST)
phase2: $(PROGRAM)

.PHONY: phase1
phase1: OBJECTS := $(phase1_OBJS) $(phase1_TEST)
phase1: $(PROGRAM)

.PHONY: clean
clean:
	$(RM) -r *.o machine.uarm.cfg term0.uarm

.PHONY: check
check: $(PROGRAM) machine.uarm.cfg
	uarm -c machine.uarm.cfg -e -x

.PHONY: $(PROGRAM)
$(PROGRAM): $(common_OBJS) $(OBJECTS) | build/

ifneq "$(MAKECMDGOALS)" "clean"
-include $(subst .o,.d,$(OBJECTS))
endif

# $(call make-depend,source-file,object-file,depend-file)
define make-depend
	$(CC) -MM -MF $3 -MP -MT $2 $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $1
endef

%.o: %.c
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(COMPILE.c) $(OUTPUT_OPTION) $<

build/:
	mkdir $@

machine.uarm.cfg: machine.uarm.cfg_template
	sed -e "s|\@BASEDIR\@|$(BASEDIR)|g" -e "s|\@CURDIR\@|$(CURDIR)|g" $< > $@
