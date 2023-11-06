CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o trapezoidal.o
	g++ main.o trapezoidal.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& ./main 12

main.o: main.cpp trapezoidal.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

trapezoidal.o: trapezoidal.cpp integral.h
	g++ trapezoidal.cpp \
		-c \
		${CXXFLAGS}
