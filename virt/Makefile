CC = clang
CFLAGS = -g

SRCS = value.c main.c memory.c pairMemory.c interpret.c
HDRS = value.h opCodes.h value.h memory.h pairMemory.h interpret.h
OBJS = $(SRCS:.c=.o)

main: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm main
