CC = clang
CFLAGS = -g

SRCS = vector.c token.c tokenizer.c tokenerror.c vector-test.c
HDRS = vector.h token.h tokenizer.h tokenerror.h
OBJS = $(SRCS:.c=.o)

vector: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm vector
