CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o midpoint.o
	g++ main.o midpoint.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& ./main 10 10000

main.o: main.cpp midpoint.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

midpoint.o: midpoint.cpp integral.h
	g++ midpoint.cpp \
		-c \
		${CXXFLAGS}
