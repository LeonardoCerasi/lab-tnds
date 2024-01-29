CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o bisection.o secant.o
	g++ main.o bisection.o secant.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& ./main

main.o: main.cpp bisection.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

bisection.o: bisection.cpp bisection.h roots.h
	g++ bisection.cpp \
		-c \
		${CXXFLAGS}

secant.o: secant.cpp secant.h roots.h
	g++ secant.cpp \
		-c \
		${CXXFLAGS}
