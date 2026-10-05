CC = cl
CFLAGS = -c

all: Matrix

Matrix: Matrix.o main.o
	$(CC) main.o Matrix.o -o Matrix

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

Matrix.o: Matrix.cpp
	$(CC) $(CFLAGS) Matrix.cpp -o Matrix.o