
BINDIR=bin
.phony: all clean ${BINDIR}

all:
SRCDIR=src
OBJECTS=${SRCDIR}/main-banker.o ${SRCDIR}/Banker.o
CXXFLAGS=-g -Wall

all: ${BINDIR}/main-banker

${BINDIR}/main-banker: ${OBJECTS} ${BINDIR}
	g++ -o $@ ${OBJECTS}

${BINDIR}:
	mkdir bin

${SRCDIR}/main-banker.o: ${SRCDIR}/main-banker.cpp ${SRCDIR}/Banker.h

${SRCDIR}/Banker.o: ${SRCDIR}/Banker.cpp ${SRCDIR}/Banker.h

clean:
	rm -R -f ${SRCDIR}/*.o ${SRCDIR}/*.h~ ${SRCDIR}/*.cpp~
	rm -R -f ${BINDIR}
