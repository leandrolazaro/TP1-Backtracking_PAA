TARGET=maze

# compiler
CC=g++
CCO=clang
# warnings
WARN=-Wall


CCFLAGS=$(WARN)

SRC= structs/cell/cell.cpp structs/maze/maze.cpp structs/stack/stack.cpp main.cpp

all:
	$(CC) -o $(TARGET) $(SRC) $(CCFLAGS) -lm -O3

debug:
	$(CC) -o $(TARGET) $(SRC) $(CCFLAGS) -lm -DDEBUG=1 -O3

run:
	./$(TARGET)

clear:
	rm $(TARGET)

clang:
	$(CCO) -o $(TARGET) $(SRC) $(CCFLAGS) -lm -O3