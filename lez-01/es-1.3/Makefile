main: main.o func.o
	g++ -Wall main.o func.o -o main

main.o: main.cpp func.h
	g++ -Wall -c main.cpp

func.o: func.cpp func.h
	g++ -Wall -c func.cpp

clean:
	rm *.o