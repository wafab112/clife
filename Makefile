UNAME_S = $(shell uname -s)

CXX = g++

CFLAGS = -std=c++11 -O3
CFLAGS += -I lib/glfw/include -IGLEW
CFLAGS += -g -glldb

LDFLAGS = lib/glfw/src/libglfw3.a -lGLEW

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)

# adds macOS frameworks, needed by GLFW, to linker (see https://www.glfw.org/docs/3.4/build_guide.html#build_link_osx)
ifeq (${UNAME_S}, Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

# adds libdl to linker
ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lm -lGL -lGLU -lX11 -lpthread
endif

.PHONY: run lib all test clean dirs

all: dirs lib build/clife

dirs:
	mkdir -p build

lib:
	cd lib/glfw && cmake . && make

run: all
	./build/clife	

build/clife: ${OBJS}
	${CXX} $^ -o $@ ${LDFLAGS}

${OBJS}:%.o: %.cpp
	${CXX} ${CFLAGS} -c $< -o $@

TEST_CFLAGS = -Itests/lib/doctest/include
TEST_LDFLAGS = 

TEST_SRC = $(wildcard tests/src/*.cpp)
TEST_OBJS = $(TEST_SRC:.cpp=.o)

test: dirs lib build/run_tests
	build/run_tests

build/run_tests: ${TEST_OBJS}
	${CXX} $^ -o $@ ${LDFLAGS} ${TEST_LDFLAGS}

${TEST_OBJS}:%.o: %.cpp
	${CXX} ${CFLAGS} ${TEST_CFLAGS} -c $< -o $@

clean:
	rm -r build
	rm ${OBJS}
	
