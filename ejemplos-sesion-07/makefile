EXEC = linuxHNK linuxHNU windowsHNK.exe
CXXFLAGS =
LDFLAGS = -lpthread

all: $(EXEC)

linuxHNK: linuxHNK.o
	$(CXX)  -o $@ $<

linuxHNU: linuxHNU.o
	$(CXX) -o $@ $< $(LDFLAGS)

windowsHNK.exe: windowsHNK.o
	x86_64-w64-mingw32-c++ -o $@ $<

windowsHNK.o: windowsHNK.cpp
	 x86_64-w64-mingw32-c++ -c $<

clean:
	rm -f *.cpp~ *.o makefile~
	rm -f $(EXEC)
