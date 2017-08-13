include ../Make.defines.linux
ROOT 	= ..
SRCS	= $(wildcard *.c)
# 3 line equals 
# PROGS   = $(patsubst %.cpp,%,$(SRCS))
#PROGS   = $(SRCS:%.cpp=%)
PROGS   = $(SRCS:.c=)
LIB_SRCS = $(wildcard *.cxx)
# remove .cxx 
OBJS= $(LIB_SRCS:.cxx=.o)

#PROGS   = $(addprefix exe_,$(SRCS:.cpp=))
all:$(PROGS)
IGNORE_WAR=-Wsign-compare

#$(PROGS):%:%.c $(LIBAPUE) $(OBJS)

$(PROGS):%:%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $^ -o $@.app $(LDFLAGS) $(LDLIBS) 

#objs:$(OBJS)
#	$(CC) $(CFLAGS) $^ -c $@.o	

# is same
#$(OBJS) :%:%.cxx
#$(OBJS):$(LIB_SRCS) $(LIBAPUE) 
#	$(CXX) -c -o $@ $(LDLIBS) $^ $(IGNORE_WAR) -I$(ROOT)/include -Wall -DLINUX -D_GNU_SOURCE

#$(OBJS):$(LIB_SRCS) $(LIBAPUE)
#	$(CXX) -c -I$(ROOT)/include -Wall -DLINUX -D_GNU_SOURCE $(EXTRA)  $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(addsuffix .app,$(PROGS)) *.o
