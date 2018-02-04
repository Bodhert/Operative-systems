.phony: clean

all: directCalling directCalling2 manualCalling manualCalling2 EjemploFork

directCalling: mifuncion.o directCalling.o
	gcc -o directCalling mifuncion.o directCalling.o

mifuncion.o: mifuncion.c constantes.h
	gcc -c mifuncion.c

directCalling.o: directCalling.c constantes.h
	gcc -c directCalling.c

directCalling2: mifuncion.o directCalling2.o
	gcc -o directCalling2 mifuncion.o directCalling2.o

directCalling2.o: directCalling2.c constantes.h
	gcc -c directCalling2.c

manualCalling: manualCalling.o
	gcc -o manualCalling manualCalling.o

manualCalling.o: manualCalling.c
	gcc -c manualCalling.c

manualCalling2: manualCalling2.o
	gcc -o manualCalling2 manualCalling2.o

manualCalling2.o: manualCalling2.c
	gcc -c manualCalling2.c

EjemploFork: EjemploFork.o
	gcc -o EjemploFork EjemploFork.o

EjemploFork.o: EjemploFork.c
	gcc -c EjemploFork.c

clean:
	rm -f mifuncion.o directCalling.o directCalling \
	      directCalling2.o directCalling2 \
	      manualCalling.o manualCalling \
	      manualCalling2.o manualCalling2 \
	      EjemploFork.o EjemploFork
