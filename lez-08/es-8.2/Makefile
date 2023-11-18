CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o
	g++ main.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& echo && ./main && echo

main.o: main.cpp arr_op.h assert.h runge_kutta.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}
