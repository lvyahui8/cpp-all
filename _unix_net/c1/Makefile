CC				= cc
PLATFORM			= OS_LINUX
CFLAGS				= -g -std=c11 -O2 -Wall
LDFLAGS				= -lunp -lpthread
SRCS=$(wildcard *.c)
PROGS=$(SRCS:.c=)

all:$(PROGS)

$(PROGS):%:%.c
	$(CC) $(CFLAGS)  $^ -o $@.app  $(LDFLAGS)

.PHONY:clean
clean:
	rm -f $(PROGS)
