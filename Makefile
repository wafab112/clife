CXX = g++

sdir = ./src
bdir = ./build
ldir = ./lib
idir = ./include

CFLAGS = -std=c++11 -I ${idir}

_target = clife
_entry = main

target = ${bdir}/${_target}
entry = ${sdir}/${_entry}.cpp

libs = 

.PHONY: all
all: ${bdir} ${target}

.PHONY: run
run: all
	${target}

${target}: ${bdir}/${_entry}.o ${bdir}
	${CXX} ${CFLAGS} $< -o $@ ${libs}

${bdir}/${_entry}.o: ${entry}
	${CXX} ${CFLAGS} -c $< -o $@

${bdir}:
	mkdir ${bdir}

tdir = ./tests
tentry = ${tdir}/src/main.cpp
tlibs = 

.PHONY: test
test: ${bdir}/run_tests
	${bdir}/run_tests

${bdir}/run_tests: ${tentry}
	${CXX} ${CFLAGS} -I ${tdir}/include ${tentry} -o ${bdir}/run_tests ${libs} ${tlibs}

.PHONY: clean
clean:
	rm -r build
	rm ${tdir}/run
