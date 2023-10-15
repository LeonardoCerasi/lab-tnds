CXXFLAGS = -g -Wall --pedantic
LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.cpp func.h pos.h
	g++ main.cpp \
		-o main \
		${CXXFLAGS} ${LIBS} ${INCS}

clean:
	rm *.o
