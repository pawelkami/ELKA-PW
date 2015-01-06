CXX = g++
LFLAGS = -Wall
CXXFLAGS = -Wall -c

start: main.o buffer.o
	$(info LACZENIE)
	$(CXX) $(LFLAGS) main.o buffer.o -lpthread -o start

main.o: main.cpp
	$(info KOMPILACJA MAIN.CPP)
	$(CXX) $(CXXFLAGS) main.cpp

buffer.o: buffer.cpp
	$(info KOMPILACJA buffer.CPP)
	$(CXX) $(CXXFLAGS) buffer.cpp

clean:
	$(info CZYSZCZENIE)
	rm *.o *~ start
