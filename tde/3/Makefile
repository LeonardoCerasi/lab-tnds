CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o
	g++ main.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& echo && ./main && echo \

main.o: main.cpp runge_kutta.h arr_op.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

clean:
	rm *o
