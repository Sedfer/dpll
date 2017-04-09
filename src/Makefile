SRC_FILES=$(wildcard *.cpp)
OBJ_FILES=$(SRC_FILES:%.cpp=../obj/%.o)
INC_FILES=$(wildcard *.h)
CC=g++
CFLAGS=-std=c++11 -Wall -static-libstdc++ -static-libgcc -O3
BIN=../bin/solver

all: dirs $(BIN)

dirs:
	@mkdir -p ../bin
	@mkdir -p ../obj

$(BIN): $(OBJ_FILES)
	@echo Linking...
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ && echo Build successfully

$(OBJ_FILES): ../obj/%.o: %.cpp $(INC_FILES)
	@echo Compilling $<...
	@$(CC) $(CFLAGS) $< -c -o $@

install: dirs $(BIN)
	@cp $(BIN) /usr/local/bin/ && echo Installed successfully

clean:
	@rm -rf ../obj $(BIN) && echo Cleared successfully
