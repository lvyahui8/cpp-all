CC				= cc
CXX				= g++
PLATFORM			= OS_LINUX
PLATFORM_LIBS			= 
PLATFORM_CXXFLAGS		= -static -DOS_LINUX -DLIT
PLATFORM_LDFLAGS		= 

CXXFLAGS += $(PLATFORM_CXXFLAGS)  $(PLATFORM_LDFLAGS)

SRCS=$(wildcard *.cc)
OBJS=$(patsubst %.cc,%.o, $(SRCS))

hosts_utils : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $@.app
clean :	
	-rm *.o *.app 

