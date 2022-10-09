CXX = g++

sdir = ./src
bdir = ./build
ldir = ./lib
idir = ./include
tdir = ./tests

CFLAGS = -std=c++11 -I ${idir}

_target = clife
_entry = main

target = ${bdir}/${_target}
entry = ${sdir}/${_entry}.cpp

all: ${bdir} ${target}

${bdir}:
	mkdir ${bdir}

${target}: ${bdir}/${_entry}.o ${bdir}
	${CXX} ${CFLAGS} $< -o $@

${bdir}/${_entry}.o: ${entry}
	${CXX} ${CFLAGS} -c $< -o $@
