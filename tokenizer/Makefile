CC = clang
CFLAGS = -g

SRCS = vector.c token.c tokenizer.c tokenerror.c linkedlist.c vector-test.c
HDRS = vector.h token.h tokenizer.h tokenerror.h linkedlist.h
OBJS = $(SRCS:.c=.o)

tokenizer: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm tokenizer
