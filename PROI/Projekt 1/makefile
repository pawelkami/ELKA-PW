CXX = g++
LFLAGS = -Wall
CXXFLAGS = -Wall -c

start: main.o LiczbaZespolona.o
	$(info LACZENIE)
	$(CXX) $(LFLAGS) main.o LiczbaZespolona.o -o start

main.o: main.cpp
	$(info KOMPILACJA MAIN.CPP)
	$(CXX) $(CXXFLAGS) main.cpp

LiczbaZespolona.o: LiczbaZespolona.cpp
	$(info KOMPILACJA LiczbaZespolona.CPP)
	$(CXX) $(CXXFLAGS) LiczbaZespolona.cpp

clean:
	$(info CZYSZCZENIE)
	rm -f *.o start
