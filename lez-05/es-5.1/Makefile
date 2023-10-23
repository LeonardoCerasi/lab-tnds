CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o particle.o
	g++ main.o particle.o \
		-o main \
		${CXXFLAGS} ${LIBS} ${INCS} \
		&& rm *.o

main.o: main.cpp particle.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

particle.o: particle.cpp particle.h
	g++ particle.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}
