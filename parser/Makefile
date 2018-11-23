
CC = clang
CFLAGS = -g

#parsetree-test.c

SRCS = parsetree.c parser.c vector.c parser-test.c
HDRS = parsetree.h parser.h vector.h
OBJS = $(SRCS:.c=.o)

parser: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm parsetree-test
