# makefile for test01.cpp

LIBS = -pthread
LIBS += -lopencv_core
LIBS += -lopencv_imgcodecs 
LIBS += -lopencv_imgproc 
LIBS += -opencv_videoio
LIBS += -opencv_objdetect
LIBS += -opencv_ml
LIBS += -llstdc++

all: test01

clean:
	rm -f test01.o

test01: test01.cpp
	gcc -c ${LIBS} test01.cpp -o test01.o 
