CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LDFLAGS=
LDDIR=
LDLIBS=-levent -lpthread -levent_pthreads
CFLAGS=-Wall -DLINUX -D_GNU_SOURCE

SRCS	= $(wildcard *.c)

PROGS   = $(SRCS:.c=)
all:$(PROGS)
$(PROGS):%:%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $^ -o $@.app $(LDFLAGS) $(LDLIBS) 

clean:
	rm -f $(addsuffix .app,$(PROGS)) 
