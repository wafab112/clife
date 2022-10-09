CXX = g++

CFLAGS = -std=c++11 -O3
CFLAGS += -I lib/glfw/include 
LDFLAGS = lib/glfw/src/libglfw3.a

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)

.PHONY: run lib all test clean dirs

all: dirs lib build/clife

dirs:
	mkdir -p build

lib:
	cd lib/glfw && cmake . && make

run: all
	./build/clife	

build/clife: ${OBJS}
	${CXX} ${LDFLAGS} $^ -o $@

${OBJS}:%.o: %.cpp
	${CXX} ${CFLAGS} -c $^ -o $@

TEST_CFLAGS = -Itests/lib/doctest/include
TEST_LDFLAGS = 

TEST_SRC = $(wildcard tests/src/*.cpp)
TEST_OBJS = $(TEST_SRC:.cpp=.o)

test: dirs lib build/run_tests
	build/run_tests

build/run_tests: ${TEST_OBJS}
	${CXX} ${LDFLAGS} ${TEST_LDFLAGS} $^ -o $@

${TEST_OBJS}:%.o: %.cpp
	${CXX} ${CFLAGS} ${TEST_CFLAGS} -c $^ -o $@

clean:
	rm -r build
	cd lib/glfw && make clean
