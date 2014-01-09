CC = gcc
CCFLAGS = -Wall
LIBRARIES = -pthread

OBJECTS_PATH = Objects
SOURCES_PATH = Sources

OBJECTS = $(OBJECTS_PATH)/Main.o $(OBJECTS_PATH)/UART.o $(OBJECTS_PATH)/Robot.o $(OBJECTS_PATH)/Network.o

all: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o Network_Control $(LIBRARIES)

$(OBJECTS_PATH)/Main.o: $(SOURCES_PATH)/Main.c $(SOURCES_PATH)/UART.h $(SOURCES_PATH)/Robot.h $(SOURCES_PATH)/Network.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Main.c -o $(OBJECTS_PATH)/Main.o

$(OBJECTS_PATH)/UART.o: $(SOURCES_PATH)/UART.c $(SOURCES_PATH)/UART.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/UART.c -o $(OBJECTS_PATH)/UART.o

$(OBJECTS_PATH)/Robot.o: $(SOURCES_PATH)/Robot.c $(SOURCES_PATH)/Robot.h $(SOURCES_PATH)/UART.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Robot.c -o $(OBJECTS_PATH)/Robot.o

$(OBJECTS_PATH)/Network.o: $(SOURCES_PATH)/Network.c $(SOURCES_PATH)/Network.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Network.c -o $(OBJECTS_PATH)/Network.o

clean:
	rm -f $(OBJECTS) Network_Control
