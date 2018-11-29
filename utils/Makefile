CC = clang
CFLAGS = -c

SRCS = vector.c
HDRS = vector.h
OBJS = $(SRCS:.c=.o) 

vector: $(OBJS)
	$(CC)  $(CFLAGS) $^

#%.o : %.c $(HDRS)
#	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
