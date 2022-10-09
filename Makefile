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
	${CXX} ${CFLAGS} $< -o $@ ${ldir}/*

${bdir}/${_entry}.o: ${entry}
	${CXX} ${CFLAGS} -c $< -o $@

${bdir}:
	mkdir ${bdir}

tdir = ./tests
tentry = ${tdir}/src/main.cpp
tlibs = 

.PHONY: test
test: ${tdir}/run
	${tdir}/run

${tdir}/run: ${tentry}
	${CXX} ${CFLAGS} -I ${tdir}/include ${tentry} -o ${tdir}/run ${libs} ${tlibs}

.PHONY: clean
clean:
	rm -r build
	rm ${tdir}/run
