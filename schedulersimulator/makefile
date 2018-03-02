.phony:	clean

EXEC=schesim
OBJECTS=main.o process.o scheduleralg.o schedulersim.o schedulers.o
CXXFLAGS=-std=c++11 -Wall $(DEBUG_MODE)

all: $(EXEC)

schesim: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp schedulersim.h scheduleralg.h process.h types.h

process.o: process.cpp process.h types.h

scheduleralg.o: scheduleralg.cpp scheduleralg.h process.h types.h

schedulersim.o: schedulersim.cpp schedulersim.h scheduleralg.h process.h types.h

schedulers.o: schedulers.cpp schedulers.h schedulersim.h scheduleralg.h process.h types.h

clean:
	rm -f $(EXEC) $(OBJECTS) *.*~ *~
