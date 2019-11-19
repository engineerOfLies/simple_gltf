##############################################################################
#
# The Linux-GCC Makefile
#
##############################################################################


#
# Compiler stuff -- adjust to your system.
#

# Linux
PROJECT = sgltf_test
CC      = gcc
#CC      = clang

OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))

LIB_PATH = ../libs
LIB_PATHS = ../simple_json/libs ../simple_logger/libs
LIB_PARAMS =$(foreach d, $(LIB_PATHS), -L$d)
LIB_LIST = ../simple_json/libs/libsj.a ../simple_logger/libs/libsl.a
STATIC_LIBS = libsgltf.a
LDFLAGS = -L$(LIB_PATH) $(foreach d, $(STATIC_LIBS),$(LIB_PATH)/$d)

INC_PATHS = ../include ../libs/include ../simple_json/include
INC_PARAMS =$(foreach d, $(INC_PATHS), -I$d)

LFLAGS = -g  -o ../$(PROJECT) -lm
CFLAGS = -g  -fPIC -Wall -pedantic -std=gnu99 -fgnu89-inline -Wno-unknown-pragmas -Wno-variadic-macros
# -fgnu89-inline 
# -std=gnu99 
# -ffast-math for relase version

DOXYGEN = doxygen

#
# Targets
#

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) $(LDFLAGS) $(LIB_LIST)

docs:
	$(DOXYGEN) ../docs/Doxyfile

sources:
	echo (patsubst %.c,%.o,$(wildcard *.c)) > makefile.sources


makefile.dep: depend

depend:
	@touch makefile.dep
	@-rm makefile.dep
	@echo Creating dependencies.
	@for i in *.c; do $(CC) $(INC) -MM $(INC_PARAMS) $$i; done > makefile.dep
	@echo Done.

clean:
	rm *.o $(LIB_PATH)/lib$(PROJECT).a

count:
	wc -l *.c $(foreach d, $(INC_PATHS), $d/*.h) makefile

static:
	ar rcs $(LIB_PATH)/lib$(PROJECT).a $(OBJECTS)

#
# Dependencies.
#

include makefile.dep

#
# The default rule.
#

.c.o:
	$(CC) $(CFLAGS) $(INC_PARAMS) -c $<


