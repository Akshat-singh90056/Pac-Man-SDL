CXX = g++
SRC = src/*.cpp
BIN = main
CXXFLAGS = -Iinclude -I$(HOME)/.local/include -I$(HOME)/.local/include/SDL3 -std=c++17
LDFLAGS = -L$(HOME)/.local/lib
LDLIBS = -lSDL3 -lSDL3_image -ldl -lm

all:
	$(CXX) $(SRC) -o $(BIN) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
