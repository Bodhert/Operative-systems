LDFLAGS=-pthread -lrt
CXXFLAGS=-Wall -g
EXEC=prodcon prodconph

.phony: clean

all: prodcon prodconph

prodcon: prodcon.o
	$(CXX) -g -o $@ $< $(LDFLAGS)

prodcon.o: prodcon.cpp

prodconph: prodconph.o
	$(CXX) -g -o $@ $< $(LDFLAGS)

prodconph.o: prodconph.cpp

clean:
	rm -f $(EXEC) *.o *.*~ *~
