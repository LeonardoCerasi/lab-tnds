CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o position.o
	g++ main.o position.o \
		-o main \
		${CXXFLAGS} ${LIBS} ${INCS} \
		&& rm *.o

main.o: main.cpp position.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

position.o: position.cpp position.h
	g++ position.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}
