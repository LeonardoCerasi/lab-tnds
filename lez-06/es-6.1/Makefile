CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o functions.o
	g++ main.o functions.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o

main.o: main.cpp functions.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

functions.o: functions.cpp functions.h func.h
	g++ functions.cpp \
		-c \
		${CXXFLAGS}
