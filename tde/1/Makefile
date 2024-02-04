CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o midpoint.o mc_integral_mean.o random_gen.o
	g++ main.o midpoint.o mc_integral_mean.o random_gen.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& echo && ./main && echo \

main.o: main.cpp midpoint.h func.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

midpoint.o: midpoint.cpp midpoint.h integral.h
	g++ midpoint.cpp \
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

clean:
	rm *o
