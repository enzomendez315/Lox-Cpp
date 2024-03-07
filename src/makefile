CC = gcc
CFLAGS = -Wall

all: clox

clox: main.o chunk.o common.o debug.o memory.o
	$(CC) $(CFLAGS) -o clox main.c chunk.c debug.c memory.c

main.o: main.c common.h chunk.h debug.h
	$(CC) $(CFLAGS) -c main.c

debug.o: debug.c debug.h chunk.h
	$(CC) $(CFLAGS) -c debug.c

chunk.o: chunk.c chunk.h common.h memory.h
	$(CC) $(CFLAGS) -c chunk.c

memory.o: memory.c memory.h common.h
	$(CC) $(CFLAGS) -c memory.c

common.o: common.h
	touch common.o

clean:
	rm -f clox *.o





# CC = gcc
# CFLAGS = -Wall -O2
# LIBS = -lm

# OBJS = driver.o kernels.o fcyc.o clock.o

# all: driver

# driver: $(OBJS) config.h defs.h fcyc.h
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o driver

# clean:
# 	-rm -f $(OBJS) driver core *~ *.o





# CC = g++
# CFLAGS = -Wall
# LIBHARU = ./libharu

# sinePDF: sinePDF.o Sine.o HaruPDF.o
# 	$(CC) $(CFLAGS) -I$(LIBHARU)/include -o sinePDF sinePDF.o Sine.o HaruPDF.o -L$(LIBHARU)/src -lhpdfs

# sinePDF.o: sinePDF.cpp HaruPDF.h
# 	$(CC) $(CFLAGS) -I$(LIBHARU)/include -c sinePDF.cpp -L$(LIBHARU)/src -lhpdfs

# HaruPDF.o: HaruPDF.h HaruPDF.cpp
# 	$(CC) $(CFLAGS) -I$(LIBHARU)/include -c HaruPDF.cpp -L$(LIBHARU)/src -lhpdfs

# Sine.o: Sine.h Sine.cpp
# 	$(CC) $(CFLAGS) -c Sine.cpp

# clean:
# 	rm -f sinePDF *.o

# # sinePDF: sinePDF.cpp HaruPDF.cpp Sine.cpp
# # 	$(CC) $(CFLAGS) -I$(LIBHARU)/include -o sinePDF sinePDF.cpp HaruPDF.cpp Sine.cpp -L$(LIBHARU)/src/ -lhpdfs