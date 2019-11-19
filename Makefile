
CFLAGS=-Wall -ggdb  -O0 -std=c++11 -g 
GAME_SOURCES=src/*.cpp test/*.cpp

GCC=g++

TEST_LIBS= -lgtest -lgtest_main -lgmock -lpthread 

.phony: all clean

all: gameTest

game: $(GAME_SOURCES) Makefile src/*.h
	@$(GCC) $(CFLAGS) $(GAME_SOURCES) $(TEST_LIBS) -o $@

gameTest: game
	@valgrind ./game

coverage:$(GAME_SOURCES) Makefile src/*.h
	@$(GCC) $(CFLAGS) -fprofile-arcs -ftest-coverage -fPIC $(GAME_SOURCES) $(TEST_LIBS) -o $@

showCoverage:coverage
	@valgrind ./coverage
	gcovr -r . -e test
	rm -f *.gcov *.gcda *.gcno

clean:
	@rm -rf $(TARGETS) 
