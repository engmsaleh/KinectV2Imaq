# File:     makefile
#              
# Purpose:  Makefile to build the Image Acquistion Toolbox demo adaptor on Linux and Mac.
#              
# Copyright 2010 - 2013 The MathWorks, Inc.
#

OS := $(shell uname)

ADAPTOR_DIR := ./build

MATLAB_ROOT := ../../../../..

ifeq ($(strip $(MATLAB_ROOT)),)
    $(error MATLAB must be on your PATH during build unless you hard code MATLAB_ROOT in the makefile.)
endif

SRC := $(shell ls *.cpp)

OBJECTS := $(SRC:.cpp=.o) 

IMDF := $(shell ls *.imdf)

LIBS := mx mwimaqmex

INCLUDE_DIRS := $(MATLAB_ROOT)/toolbox/imaq/imaqadaptors/kit/include

ifeq ($(OS), Linux) 
    MLARCH := glnxa64
    CPPFLAGS += \
		$(addprefix -I,$(INCLUDE_DIRS)) \
		-DARRAY_ACCESS_INLINING -D_POSIX_C_SOURCE=199506L \
		-O2 -pipe -pthread -fPIC -std=c++98 -fvisibility=hidden \
		-fno-omit-frame-pointer \
		-W -Wcast-align -Wall -Wshadow -Wwrite-strings -Wpointer-arith \
		-Wcast-qual -Wno-unused -Woverloaded-virtual -Wnon-virtual-dtor -Wno-ignored-qualifiers -Werror
    LDFLAGS += \
		$(addprefix -l,$(LIBS)) \
		$(addprefix -L,$(LIBPATH)) \
		-shared  -Wl,--no-undefined -pthread \
		-Wl,--rpath,\$$ORIGIN:\$$ORIGIN/../../../../bin/$(MLARCH):\$$ORIGIN/../../../../sys/os/$(MLARCH)

    RESULT := $(ADAPTOR_DIR)/mwdemoimaq.so

else ifeq ($(OS), Darwin) 
    MLARCH := maci64
    ISMOUNTLION := $(shell expr `sysctl -a kern.osrelease | cut -f 2 -d " " | cut -f 1 -d "."` \>= 12)
    ifeq ($(ISMOUNTLION), 1)
        CXX := xcrun -sdk macosx10.7 c++
        CPPFLAGS += -isysroot $(shell xcode-select --print-path)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk
        LDFLAGS += -Wl,-syslibroot $(shell xcode-select --print-path)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk
    endif

    CPPFLAGS += \
	$(addprefix -I,$(INCLUDE_DIRS)) \
	-DARRAY_ACCESS_INLINING \
	-O2 -pipe -fno-common -arch x86_64 \
	-std=c++98 -fvisibility=hidden \
	-g -D_REENTRANT -W -Wcast-align \
	-Wall -Wshadow -Wwrite-strings -Wpointer-arith -Wcast-qual -Wno-unused -Wno-unused-parameter \
	-Woverloaded-virtual -Wnon-virtual-dtor -Werror
    LDFLAGS += \
	$(addprefix -l,$(LIBS)) \
	$(addprefix -L,$(LIBPATH)) \
	-dynamiclib -single_module \
	-install_name @loader_path/mwdemoimaq.dylib -arch x86_64 \
	-Wl,-rpath,@loader_path -Wl,-rpath,@loader_path/../../../../bin/$(MLARCH) -Wl,-rpath,@loader_path/../../../../sys/os/$(MLARCH)

    RESULT := $(ADAPTOR_DIR)/mwdemoimaq.dylib

else
    $(error Unsupported operating system.)
endif 

LIBPATH := $(MATLAB_ROOT)/bin/$(MLARCH) $(ADAPTOR_DIR)

all: build

build: $(RESULT)

$(RESULT): $(OBJECTS)
	mkdir -p $(ADAPTOR_DIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ 
	cp -f $(IMDF) $(ADAPTOR_DIR)/.

clean:
	rm -f $(OBJECTS)
	rm -f $(RESULT)
	rm -f $(ADAPTOR_DIR)/$(IMDF)
