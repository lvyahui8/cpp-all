CC				= cc
CXX				= g++
PLATFORM			= OS_LINUX
PLATFORM_LDFLAGS		= -pthread
PLATFORM_LIBS			=
PLATFORM_CXXFLAGS		= -static -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11
PLATFORM_SHARED_EXT		= so
PLATFORM_SHARED_VERSIONED	= true

CXXFLAGS += $(PLATFORM_CXXFLAGS)  $(PLATFORM_LDFLAGS)

SRCS=$(wildcard *.cc)
PROGS=$(SRCS:.cc=)

all:$(PROGS)
$(PROGS):%:%.cc
	$(CXX) $^ -o $@.app $(CXXFLAGS)

.PHONY:clean
clean:
	rm -f $(PROGS)
