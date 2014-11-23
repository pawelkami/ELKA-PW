CXX = g++
LFLAGS = -Wall
CXXFLAGS = -Wall -c -std=c++11

start: main.o Zbior.o
	$(info LACZENIE)
	$(CXX) $(LFLAGS) main.o Zbior.o -o start

main.o: main.cpp
	$(info KOMPILACJA MAIN.CPP)
	$(CXX) $(CXXFLAGS) main.cpp

Zbior.o: Zbior.cpp Zbior.h
	$(info KOMPILACJA Zbior.CPP)
	$(CXX) $(CXXFLAGS) Zbior.cpp

clean:
	$(info CZYSZCZENIE)
	rm -f *.o start
