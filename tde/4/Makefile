CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o bisection.o trapezoidal.o
	g++ main.o bisection.o trapezoidal.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& echo && ./main && echo \

main.o: main.cpp bisection.h trapezoidal.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

bisection.o: bisection.cpp bisection.h roots.h sign.h
	g++ bisection.cpp \
		-c \
		${CXXFLAGS} ${INCS}

trapezoidal.o: trapezoidal.cpp trapezoidal.h integral.h
	g++ trapezoidal.cpp \
		-c \
		${CXXFLAGS} ${INCS}

clean:
	rm *o
