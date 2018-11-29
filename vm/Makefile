CC = clang
CFLAGS = -g -I'../parser'

SRCS = memory.c chunk.c debug.c value.c vm.c compiler.c main.c ../parser/parsetree.c ../parser/parser.c ../parser/vector.c
HDRS = memory.h chunk.h debug.h value.h vm.h compiler.h common.h ../parser/parsetree.h ../parser/parser.h ../parser/vector.h
OBJS = $(SRCS:.c=.o)

main: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@

%.o : %.c $(HDRS)
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
	rm main
