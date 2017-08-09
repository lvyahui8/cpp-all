include ../Make.defines.linux
ROOT 	= ..
SRCS	= $(wildcard *.c)
# 3 line equals 
# PROGS   = $(patsubst %.cpp,%,$(SRCS))
#PROGS   = $(SRCS:%.cpp=%)
PROGS   = $(SRCS:.c=)
#PROGS   = $(addprefix exe_,$(SRCS:.cpp=))
all:$(PROGS)
$(PROGS):%:%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $^ -o $@.app $(LDFLAGS) $(LDLIBS) 

clean:
	rm -f $(addsuffix .app,$(PROGS)) 
