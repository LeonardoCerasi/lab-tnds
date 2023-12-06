CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o random_gen.o mc_integral_mean.o mc_integral_hm.o
	g++ main.o random_gen.o mc_integral_mean.o mc_integral_hm.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o \
		&& echo && ./main && echo \

main.o: main.cpp random_gen.h mc_integral_mean.h assert.h func.h integrals.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

random_gen.o: random_gen.cpp random_gen.h
	g++ random_gen.cpp \
		-c \
		${CXXFLAGS} ${INCS}

mc_integral_mean.o: mc_integral_mean.cpp mc_integral_mean.h mc_integral.h
	g++ mc_integral_mean.cpp \
		-c \
		${CXXFLAGS} ${INCS}

mc_integral_hm.o: mc_integral_hm.cpp mc_integral_hm.h mc_integral.h
	g++ mc_integral_hm.cpp \
		-c \
		${CXXFLAGS} ${INCS}
