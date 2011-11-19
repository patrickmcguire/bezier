CC = g++

UNI = pjm2119
Theme = 05
Milestone = 01

SRC = main.cpp Curve.cpp CurveFile.cpp
TARGET = main_t$(Theme)m$(Milestone)

OBJS = main.o Curve.o CurveFile.o
HEADERS = Curve.h CurveFile.h

INCDIRS = -I/usr/include -I/usr/local/include
LIBDIRS = -L/usr/lib -L/usr/local/lib -L/opt/local/lib
CFLAGS = -Wall -g $(INCLUDE)
LDFLAGS = -lglut -lGL -lGLU -lm

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
INCDIRS := $(INCDIRS) -I/opt/local/include
LIBDIRS = $(LIBDIRS) -L/opt/local/lib/boost
LDFLAGS = -framework GLUT -framework OpenGL                                                                                                                                  
CFLAGS = -Wall -g $(INCDIRS) $(LIBDIR) -framework GLUT -framework OpenGL $(LDFLAGS)
endif

all: $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(HEADERS)
main.o: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c main.cpp $(HEADERS)
Curve.o: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c Curve.cpp $(HEADERS)
CurveFile.o: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c CurveFile.cpp $(HEADERS)
clean:
	rm -f $(TARGET) $(TARGET_CREATIVE) $(OBJS) *.gch
