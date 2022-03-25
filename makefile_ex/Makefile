CC=gcc
CFLAGS=-c -Wall

all: hello

hello: bin/main.o bin/sum.o bin/new_script.o
	$(CC) bin/main.o bin/sum.o bin/new_script.o -o hello

bin/main.o: src/main.c include/functions.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

bin/sum.o: src/sum.c include/functions.h
	$(CC) $(CFLAGS) -c src/sum.c -o bin/sum.o

bin/new_script.o: src/new_script.c include/functions.h
	$(CC) $(CFLAGS) -c src/new_script.c -o bin/new_script.o

clean:
	rm -rf bin/*.o hello
