CC = gcc
CCFLAGS = -Wall -g
#-O3
LIBRARIES = -pthread -lgmp -lssl -lcrypto

OBJECTS_PATH = Objects
SOURCES_PATH = Sources
SOURCES_CRYPTO_PATH = $(SOURCES_PATH)/Crypto

OBJECTS_CRYPTO = $(OBJECTS_PATH)/Elliptic_Curves.o $(OBJECTS_PATH)/Point.o $(OBJECTS_PATH)/Utils.o $(OBJECTS_PATH)/AES.o $(OBJECTS_PATH)/DSA.o
OBJECTS = $(OBJECTS_CRYPTO) $(OBJECTS_PATH)/Main.o $(OBJECTS_PATH)/UART.o $(OBJECTS_PATH)/Robot.o $(OBJECTS_PATH)/Network.o $(OBJECTS_PATH)/Security.o $(OBJECTS_PATH)/Log.o $(OBJECTS_PATH)/Security_Server.o

all: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o Network_Control $(LIBRARIES)

$(OBJECTS_PATH)/Main.o: $(SOURCES_PATH)/Main.c $(SOURCES_PATH)/UART.h $(SOURCES_PATH)/Robot.h $(SOURCES_PATH)/Network.h $(SOURCES_PATH)/Log.h $(SOURCES_PATH)/Security_Server.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Main.c -o $(OBJECTS_PATH)/Main.o

$(OBJECTS_PATH)/UART.o: $(SOURCES_PATH)/UART.c $(SOURCES_PATH)/UART.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/UART.c -o $(OBJECTS_PATH)/UART.o

$(OBJECTS_PATH)/Robot.o: $(SOURCES_PATH)/Robot.c $(SOURCES_PATH)/Robot.h $(SOURCES_PATH)/UART.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Robot.c -o $(OBJECTS_PATH)/Robot.o

$(OBJECTS_PATH)/Network.o: $(SOURCES_PATH)/Network.c $(SOURCES_PATH)/Network.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Network.c -o $(OBJECTS_PATH)/Network.o

$(OBJECTS_PATH)/Security.o: $(SOURCES_PATH)/Security.c $(SOURCES_PATH)/Security.h $(SOURCES_PATH)/Network.h $(SOURCES_PATH)/Log.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Security.c -o $(OBJECTS_PATH)/Security.o

$(OBJECTS_PATH)/Log.o: $(SOURCES_PATH)/Log.c $(SOURCES_PATH)/Log.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Log.c -o $(OBJECTS_PATH)/Log.o

$(OBJECTS_PATH)/Security_Server.o: $(SOURCES_PATH)/Security_Server.c $(SOURCES_PATH)/Security_Server.h $(SOURCES_PATH)/Security.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Security_Server.c -o $(OBJECTS_PATH)/Security_Server.o

$(OBJECTS_PATH)/Elliptic_Curves.o: $(SOURCES_CRYPTO_PATH)/Elliptic_Curves.c $(SOURCES_CRYPTO_PATH)/Elliptic_Curves.h $(SOURCES_CRYPTO_PATH)/Point.h
	$(CC) $(CCFLAGS) -c $(SOURCES_CRYPTO_PATH)/Elliptic_Curves.c -o $(OBJECTS_PATH)/Elliptic_Curves.o

$(OBJECTS_PATH)/Point.o: $(SOURCES_CRYPTO_PATH)/Point.c $(SOURCES_CRYPTO_PATH)/Point.h
	$(CC) $(CCFLAGS) -c $(SOURCES_CRYPTO_PATH)/Point.c -o $(OBJECTS_PATH)/Point.o

$(OBJECTS_PATH)/Utils.o: $(SOURCES_CRYPTO_PATH)/Utils.c $(SOURCES_CRYPTO_PATH)/Utils.h
	$(CC) $(CCFLAGS) -c $(SOURCES_CRYPTO_PATH)/Utils.c -o $(OBJECTS_PATH)/Utils.o

$(OBJECTS_PATH)/AES.o: $(SOURCES_CRYPTO_PATH)/AES.c $(SOURCES_CRYPTO_PATH)/AES.h
	$(CC) $(CCFLAGS) -c $(SOURCES_CRYPTO_PATH)/AES.c -o $(OBJECTS_PATH)/AES.o

$(OBJECTS_PATH)/DSA.o: $(SOURCES_CRYPTO_PATH)/DSA.c $(SOURCES_CRYPTO_PATH)/DSA.h
	$(CC) $(CCFLAGS) -c $(SOURCES_CRYPTO_PATH)/DSA.c -o $(OBJECTS_PATH)/DSA.o

clean:
	rm -f $(OBJECTS) Network_Control
