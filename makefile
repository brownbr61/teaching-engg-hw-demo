
all:
	g++ test.c -o test.o
clean:
	rm ./test.o
test:
	g++ test.c -o test.o
	./test.o