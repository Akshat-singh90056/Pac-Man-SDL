
all:
	g++ src/*.cpp -o main -I/usr/local/include -Iinclude -L/usr/local/lib -lSDL3


run:
	g++ src/*.cpp -o main -I/usr/local/include -Iinclude  -L/usr/local/lib -lSDL3
	./main

clean:
	rm main