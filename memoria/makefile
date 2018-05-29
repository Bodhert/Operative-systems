
all: control rmmem visor tuberiaEjemplo fileBinExa fileEwe

control: control.o
	$(CXX) -o $@ $^ -lrt

rmmem: rmmem.o
	$(CXX) -o $@ $^ -lrt

visor: visor.o
	$(CXX) -o $@ $^ -lrt

tuberiaEjemplo: tuberiaEjemplo.o
	$(CXX) -o $@ $^

fileBinExa: fileBinExa.o
	$(CXX) -o $@ $^

fileEwe: fileEwe.o
	$(CXX) -o $@ $^

control.o: control.cpp

rmmem.o: rmmem.cpp

visor.o: visor.cpp

tuberiaEjemplo.o: tuberiaEjemplo.cpp

fileBinExa.o: fileBinExa.cpp

fileEwe.o: fileEwe.cpp

clean:
	rm -f control rmmem visor tuberiaEjemplo fileBinExa fileEwe
	rm -f *.o *.*~ *~ 
