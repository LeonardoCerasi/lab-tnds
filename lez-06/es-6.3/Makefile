CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o functions.o bisection.o secant.o
	g++ main.o functions.o bisection.o secant.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& ./main 16 > log.log

main.o: main.cpp functions.h bisection.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

functions.o: functions.cpp functions.h func.h
	g++ functions.cpp \
		-c \
		${CXXFLAGS}

bisection.o: bisection.cpp bisection.h func.h roots.h
	g++ bisection.cpp \
		-c \
		${CXXFLAGS}

secant.o: secant.cpp secant.h func.h roots.h
	g++ secant.cpp \
		-c \
		${CXXFLAGS}
