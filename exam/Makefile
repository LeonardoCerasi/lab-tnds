CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o mc_integral_mean.o random_gen.o simpson.o
	g++ main.o mc_integral_mean.o random_gen.o simpson.o \
		-o main \
		${CXXFLAGS} ${LIBS}

main.o: main.cpp arr_op.h mc_integral_mean.h random_gen.h simpson.h runge_kutta.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

mc_integral_mean.o: mc_integral_mean.cpp mc_integral_mean.h mc_integral.h random_gen.h
	g++ mc_integral_mean.cpp \
		-c \
		${CXXFLAGS} ${INCS}

random_gen.o: random_gen.cpp random_gen.h
	g++ random_gen.cpp \
		-c \
		${CXXFLAGS} ${INCS}

simpson.o: simpson.cpp simpson.h integral.h
	g++ simpson.cpp \
		-c \
		${CXXFLAGS} ${INCS}

esegui:
	echo && ./main && echo

clean:
	rm *.o
