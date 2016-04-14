CC		= gcc
CXX	= g++
RM		= rm -f
MAKE	= make
MAKEDIR = mkdir -p
COPY	= cp
AR		= ar
CPPFLAGS = -O3 -std=c++11
RELEASE = exe 

DIRS := ./
SOURCE_FILES_CPP := $(foreach d, $(DIRS), $(wildcard $(d)*.cpp) )
SOURCE_FILES_CC := $(foreach d, $(DIRS), $(wildcard $(d)*.cc) )

OBJECT_CPP = $(patsubst %.cpp, %.o, $(SOURCE_FILES_CPP))
OBJECT_CC = $(patsubst %.cc, %.o, $(SOURCE_FILES_CC))
EXE_CPP = $(patsubst %.cpp, %.exe, $(SOURCE_FILES_CPP))

INCLUDE_DIR = ../include
LIB_DIR =
LIB_NAME = pthread

OBJECT = $(OBJECT_CPP) $(OBJECT_CC)
LINK_LIB = $(addprefix -l, $(LIB_NAME))
LINK_PATH = $(addprefix -L, $(LIB_DIR))
INCLUDE_PATH = $(addprefix -I,$(INCLUDE_DIR))

%.o : %.cc
	$(CXX) $(CPPFLAGS) $(INCLUDE_PATH) -c $< -o $@

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDE_PATH) -c $< -o $@

%.exe : %.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDE_PATH) $< -o $@ $(LINK_PATH) $(LINK_LIB)

all:  $(EXE_CPP)

clean:
	$(RM) $(EXE_CPP)
