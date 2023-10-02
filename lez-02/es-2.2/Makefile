CXXFLAGS = -g -Wall --pedantic

main: main.o func.o vect.o
	g++ main.o func.o vect.o \
		-o main

main.o: main.cpp func.h vect.h
	g++ main.cpp \
		-c $(CXXFLAGS)

func.o: func.cpp func.h vect.h
	g++ func.cpp \
		-c $(CXXFLAGS)

vect.o: vect.cpp vect.h
	g++ vect.cpp \
		-c $(CXXFLAGS)

clean:
	rm *.o