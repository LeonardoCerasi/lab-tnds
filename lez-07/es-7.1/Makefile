CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o simpson.o
	g++ main.o simpson.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& ./main 10 10000

main.o: main.cpp simpson.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

simpson.o: simpson.cpp integral.h
	g++ simpson.cpp \
		-c \
		${CXXFLAGS}
