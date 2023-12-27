CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o random_gen.o prism.o
	g++ main.o random_gen.o prism.o \
		-o main \
		${CXXFLAGS} ${LIBS} \
		&& rm *.o && rm hist/* \
		&& echo && ./main && echo \

main.o: main.cpp random_gen.h assert.h func.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${INCS}

random_gen.o: random_gen.cpp random_gen.h
	g++ random_gen.cpp \
		-c \
		${CXXFLAGS} ${INCS}

prism.o: prism.cpp prism.h random_gen.h
	g++ prism.cpp \
		-c \
		${CXXFLAGS} ${INCS}
