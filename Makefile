CC=gcc
CFLAGS=-c -v
LDFLAGS=
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
LIBRARIES=-L/mingw64/lib -L/c/'Program Files'/'IVI Foundation'/VISA/Win64/Lib_x64/msc -lvisa64
INC=-I/c/'Program Files'/'IVI Foundation'/VISA/Win64/Include
EXECUTABLE=p4600visa
VPATH = src include build /c/'Program Files'/'IVI Foundation'/VISA/Win64/Include

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) ./build/$(OBJECTS) $(LIBRARIES)  -o ./dist/$@

$(OBJECTS): $(SOURCES)
	$(CC) $(INC) $(CFLAGS) $< -o ./build/$@