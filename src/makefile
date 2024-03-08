CC = gcc
CFLAGS = -Wall

all: clox

# clox: main.o chunk.o common.o debug.o memory.o
# 	$(CC) $(CFLAGS) -o clox main.o chunk.o common.o debug.o memory.o

clox: main.o chunk.o common.o debug.o memory.o value.o vm.o
	$(CC) $(CFLAGS) -o clox $^

main.o: main.c common.h chunk.h debug.h vm.h
	$(CC) $(CFLAGS) -c main.c

vm.o: vm.c vm.h chunk.h common.h debug.h value.h
	$(CC) $(CFLAGS) -c vm.c

value.o: value.c value.h common.h memory.h
	$(CC) $(CFLAGS) -c value.c

debug.o: debug.c debug.h chunk.h value.h
	$(CC) $(CFLAGS) -c debug.c

chunk.o: chunk.c chunk.h common.h memory.h value.h
	$(CC) $(CFLAGS) -c chunk.c

memory.o: memory.c memory.h common.h
	$(CC) $(CFLAGS) -c memory.c

common.o: common.h
	touch common.o

clean:
	rm -f clox *.o