CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.o position.o particle.o vector_field.o point_particle.o spherical_body.o
	g++ main.o position.o particle.o vector_field.o point_particle.o spherical_body.o \
		-o main \
		${CXXFLAGS} ${LIBS} ${INCS} \
		&& rm *.o

main.o: main.cpp position.h particle.h vector_field.h point_particle.h
	g++ main.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

position.o: position.cpp position.h
	g++ position.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

particle.o: particle.cpp particle.h
	g++ particle.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

vector_field.o: vector_field.cpp vector_field.h position.h
	g++ vector_field.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

point_particle.o: point_particle.cpp position.h particle.h vector_field.h point_particle.h
	g++ point_particle.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}

spherical_body.o: spherical_body.cpp position.h vector_field.h
	g++ spherical_body.cpp \
		-c \
		${CXXFLAGS} ${LIBS} ${INCS}
