CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o functions.o bisection.o
	g++ main.o functions.o bisection.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o

main.o: main.cpp functions.h bisection.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

functions.o: functions.cpp functions.h func.h
	g++ functions.cpp \
		-c \
		${CXXFLAGS}

bisection.o: bisection.cpp bisection.h sign.h func.h roots.h
	g++ bisection.cpp \
		-c \
		${CXXFLAGS}
