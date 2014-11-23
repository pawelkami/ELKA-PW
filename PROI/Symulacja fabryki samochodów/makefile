CXX = g++
LFLAGS = -Wall
CXXFLAGS = -Wall -c -std=c++11

start: main.o
	$(info LACZENIE)
	$(CXX) $(LFLAGS) main.o -o start

main.o: main.cpp watki.h Opona.h Karoseria.h OponaKaroseria.h Silnik.h KaroseriaSilnik.h Samochod.h dane.h PomalowanaKaroseria.h
	$(info KOMPILACJA MAIN.CPP)
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	$(info CZYSZCZENIE)
	rm -f *.o start
