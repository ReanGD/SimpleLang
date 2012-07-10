ifeq ($(BUILD_CPP), 1)
CC      := g++
EXT     := .cpp
else
CC      := gcc
EXT     := .c
endif
CFLAGS  := -MD -pipe $(BUILD_CFLAGS)
LCFLAGS := -s -pipe $(BUILD_LCFLAGS)
ROOTINC := src
ROOTSRC := src
SRC     := $(BUILD_SRC)
INC     := . gen antlr/include
LIBS    := $(BUILD_LIBS)
LIBDIRS := ../../bin

relative_inc_dirs := $(addprefix ../../$(ROOTINC)/, $(INC))
relative_src_dirs := $(addprefix ../../$(ROOTSRC)/, $(SRC))
o_dirs            := $(addprefix $(ROOTSRC)/, $(SRC))
c_files           := $(patsubst ../../%, %, $(wildcard $(addsuffix /*$(EXT), $(relative_src_dirs))))
o_files           := $(c_files:$(EXT)=.o)

all: obj_dirs $(program_name)

$(program_name): $(o_files)
	$(CC) -o $@ $(o_files) $(LCFLAGS) $(addprefix -L , $(LIBDIRS)) $(addprefix -l , $(LIBS))

obj_dirs:
	@mkdir -p $(o_dirs)

VPATH := ../../

%.o: %$(EXT)
	$(CC) -o $@ -c $< $(CFLAGS) $(BUILD_DEFS) $(addprefix -I, $(relative_inc_dirs))

.PHONY: clean

clean:
	rm -rf bin obj

include $(wildcard $(addsuffix /*.d, $(o_dirs)))