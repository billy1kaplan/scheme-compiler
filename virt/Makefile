CC = clang
CFLAGS = -g -Wall

SRCS = value.c main.c memory.c pairMemory.c interpret.c operations.c symboltable.c environment.c constants.c
HDRS = value.h opCodes.h value.h memory.h pairMemory.h operations.h constants.h symboltable.h environment.h interpret.h
OBJS = $(SRCS:.c=.o)

main: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm main
