
CFLAGS=-Wall -ggdb  -O0 -std=c++11 -g

GAME_SOURCES=src/*.cpp test/*.cpp

GCC=g++

TEST_LIBS= -lgtest -lgtest_main -lgmock -lpthread 

.phony: all clean

all: game gameTest

game: $(GAME_SOURCES) Makefile src/*.h
	@$(GCC) $(CFLAGS) $(GAME_SOURCES) $(TEST_LIBS) -o $@

gameTest: game
	@valgrind ./game

clean:
	@rm -rf $(TARGETS) 
