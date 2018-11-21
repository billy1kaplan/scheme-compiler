
CC = clang
CFLAGS = -g

SRCS = parsetree.c parsetree-test.c
HDRS = parsetree.h
OBJS = $(SRCS:.c=.o)

parsetree-test: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm parsetree-test
