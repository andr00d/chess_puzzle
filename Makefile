
CFLAGS=-Wall -ggdb  -O0 -std=c++11 -g 
TEST_SOURCES:= $(filter-out src/UI.cpp, $(wildcard src/*.cpp))
TEST_SOURCES+= $(wildcard test/*.cpp)

UI_SOURCES=src/*.cpp

GCC=g++

TEST_LIBS= -lgtest -lgtest_main -lgmock -lpthread 

.phony: all clean

all: chessTest

chessTest: $(TEST_SOURCES) Makefile src/*.h
	@$(GCC) $(CFLAGS) $(TEST_SOURCES) $(TEST_LIBS) -o $@ || exit 1
	valgrind ./chessTest

UI: $(UI_SOURCES) Makefile src/*.h
	@$(GCC) $(CFLAGS) $(UI_SOURCES) $(TEST_LIBS) -o $@

coverage:$(TEST_SOURCES) Makefile src/*.h
	@$(GCC) $(CFLAGS) -fprofile-arcs -ftest-coverage -fPIC $(TEST_SOURCES) $(TEST_LIBS) -o $@
	valgrind ./coverage
	gcovr -r . -e test
	rm -f *.gcov *.gcda *.gcno coverage

clean:
	@rm -rf chessTest UI
