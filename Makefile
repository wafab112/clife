UNAME_S = $(shell uname -s)

CXX = g++

INCLUDES = lib/glfw/include GLEW

CFLAGS = -std=c++11
CFLAGS += $(addprefix -I ,${INCLUDES})

RELEASE_CLAGS = -O3
DBG_CFLAGS = -g -glldb -Ddebug -O0

LDFLAGS = lib/glfw/src/libglfw3.a -lGLEW

CTAGS_FLAGS = -R --c++-kinds=+p --fields=+iaS --extra=+q ${INCLUDES}

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)
DBG_OBJS = $(SRC:.cpp=.dbg.o)

# adds macOS frameworks, needed by GLFW, to linker (see https://www.glfw.org/docs/3.4/build_guide.html#build_link_osx)
ifeq (${UNAME_S}, Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

# adds libdl to linker
ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lm -lGL -lGLU -lX11 -lpthread
endif

.PHONY: run lib all test clean dirs debug

all: tags dirs lib build/clife

tags:
	ctags ${CTAGS_FLAGS}

dirs:
	mkdir -p build
	mkdir -p debug

lib:
	cd lib/glfw && cmake . && make

run: all
	./build/clife	

debug: dirs lib debug/clife
	./debug/clife

build/clife: ${OBJS}
	${CXX} $^ -o $@ ${LDFLAGS}

debug/clife: ${DBG_OBJS}
	${CXX} $^ -o $@ ${LDFLAGS}

${OBJS}:%.o: %.cpp
	${CXX} ${CFLAGS} ${RELEASE_CLAGS} -c $< -o $@

${DBG_OBJS}:%.dbg.o: %.cpp
	${CXX} ${CFLAGS} ${DBG_CFLAGS} -c $< -o $@

TEST_CFLAGS = -Itests/lib/doctest/include -Isrc
TEST_LDFLAGS = 

TEST_SRC = $(wildcard tests/src/*.cpp)
TEST_OBJS = $(TEST_SRC:.cpp=.o)

test: dirs lib build/run_tests
	build/run_tests

build/run_tests: ${TEST_OBJS} $(filter-out build/main.o, $(OBJS))
	${CXX} $^ -o $@ ${LDFLAGS} ${TEST_LDFLAGS}

${TEST_OBJS}:%.o: %.cpp
	${CXX} ${CFLAGS} ${TEST_CFLAGS} -c $< -o $@

clean:
	rm -r build
	rm -r debug
	rm src/*.o
