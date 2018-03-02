.phony: clean

EXEC=ProcesoCreador ProcesoDestructor ProcesoEsperaSinc ProcesoEnviaSinc

CXXFLAGS=-Wall

all: $(EXEC)

ProcesoCreador: ProcesoCreador.o
	$(CXX) -o $@ $<

ProcesoCreador.o: ProcesoCreador.cpp

ProcesoDestructor: ProcesoDestructor.o
	$(CXX) -o $@ $<

ProcesoDestructor.o: ProcesoDestructor.cpp

ProcesoEsperaSinc: ProcesoEsperaSinc.o
	$(CXX) -o $@ $<

ProcesoEsperaSinc.o: ProcesoEsperaSinc.cpp

ProcesoEnviaSinc: ProcesoEnviaSinc.o
	$(CXX) -o $@ $<

ProcesoEnviaSinc.o: ProcesoEnviaSinc.cpp

clean:
	rm -f $(EXEC) *.o *.*~ *~
