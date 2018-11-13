CC = clang
CFLAGS = -g

SRCS = vector.c vector-test.c
HDRS = vector.h
OBJS = $(SRCS:.c=.o)

vector: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm vector
