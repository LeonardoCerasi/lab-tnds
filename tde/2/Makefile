CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o random_gen.o
	g++ main.o random_gen.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& echo && ./main && echo \

main.o: main.cpp runge_kutta.h random_gen.h func.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

random_gen.o: random_gen.cpp random_gen.h
	g++ random_gen.cpp \
		-c \
		${CXXFLAGS} ${INCS}

clean:
	rm *o
