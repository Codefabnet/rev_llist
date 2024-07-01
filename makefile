
############################################################
# All targets
############################################################

TARGETS := rev_llist

############################################################
# Common build rules
############################################################
OBJDIR := ./obj
OUTPUTDIR := ./output
SOURCEDIR := ./source

COMPILEFLAGS := -g -Wall
#COMPILEFLAGS += -ffunction-sections
#LINKERFLAGS := -Wl,-Map=$(OUTPUTDIR)/out.map
#LINKERFLAGS += -Wl,--print-map>$(OUTPUTDIR)/outmap.txt
#LINKERFLAGS += -Wl,--cref
#LINKERFLAGS += -Wl,--gc-sections

$(TARGETS): | $(OUTPUTDIR)

$(OUTPUTDIR):
	mkdir $(OUTPUTDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OUTPUTDIR)
	rm -rf $(OBJDIR)

############################################################

REV_LLIST_DIR := ./source

REV_LLIST_OBJECTS := $(addprefix $(OBJDIR)/, \
             rev_llist.o \
             rev_llist_funcs.o \
             rev_llist_algorithm.o \
	     )

REV_LLIST_HEADERS := $(REV_LLIST_DIR)/rev_llist.h \
                     $(REV_LLIST_DIR)/rev_llist_algorithm.h

############################################################

rev_llist: $(REV_LLIST_OBJECTS)
	gcc $(LINKERFLAGS) $(REV_LLIST_OBJECTS) -o $(OUTPUTDIR)/$@

$(OBJDIR)/%.o : $(REV_LLIST_DIR)/%.c $(REV_LLIST_HEADERS) $(COMMON_HEADERS)
	gcc $(COMPILEFLAGS) -c $< -o $@

$(REV_LLIST_OBJECTS): | $(OBJDIR)

