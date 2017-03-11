all: test

test: build/main.o build/vct.o
	gcc -Wall -o test.exe build/vct.o build/main.o
	
debug: clean src/main.c src/vct.c
	gcc -Wall -O0 -g3 -o test.exe src/vct.c src/main.c

build/main.o: src/main.c
	gcc -c -o build/main.o src/main.c

build/vct.o: src/vct.c
	gcc -c -o build/vct.o src/vct.c

clean:
	rm -rf build/* test.exe