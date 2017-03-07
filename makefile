all: test

test: build/main.o build/vct.o
	gcc -Wall -o build/test.exe build/vct.o build/main.o

build/main.o: src/main.c
	gcc -c -o build/main.o src/main.c

build/vct.o: src/vct.c
	gcc -c -o build/vct.o src/vct.c

clean:
	rm -rf build/*