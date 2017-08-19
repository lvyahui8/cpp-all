CC 					= cc
CXX					= g++
PLATFORM			= OS_LINUX
PLATFORM_LIBS			= 
PLATFORM_CXXFLAGS		= -static 
PLATFORM_LDFLAGS		= -lcurl  

CXXFLAGS += $(PLATFORM_CXXFLAGS)  $(PLATFORM_LDFLAGS)

SRCS=$(wildcard *.cc)
OBJS=$(patsubst %.cc,%.o, $(SRCS))

log_agent : $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) /usr/local/curl/lib/libcurl.a -o $@.app

clean :	
	-rm *.o *.app  

