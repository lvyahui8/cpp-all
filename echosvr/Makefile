CC=cc
CXX=g++
PLATFORM=OS_LINUX
PLATFORM_LDFLAGS=-pthread -L/root/work/handy
PLATFORM_LIBS=
PLATFORM_CCFLAGS=  -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11 -I/root/work/handy
PLATFORM_CXXFLAGS=  -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11 -I/root/work/handy
PLATFORM_SHARED_CFLAGS=-fPIC
PLATFORM_SHARED_EXT=so
PLATFORM_SHARED_LDFLAGS=-shared -Wl,-soname -Wl,
PLATFORM_SHARED_VERSIONED=true
CXXFLAGS += $(PLATFORM_CXXFLAGS) -lhandy $(PLATFORM_LDFLAGS)
SRCS=$(wildcard *.cpp)
PROGS=$(SRCS:.cpp=)

all:$(PROGS)
$(PROGS):%:%.cpp
	$(CXX) $^ -o $@ $(CXXFLAGS)

.PHONY:clean
clean:
	rm -f $(PROGS)
