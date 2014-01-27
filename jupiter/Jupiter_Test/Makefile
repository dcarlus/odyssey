CC = gcc
CCFLAGS = -Wall -g
LIBRARIES = -lgmp -lssl -lcrypto

OBJECTS_PATH = Objects
SOURCES_PATH = ../Network_Control/Sources
SOURCES_CRYPTO_PATH = $(SOURCES_PATH)/Crypto

OBJECTS_CRYPTO = $(OBJECTS_PATH)/Elliptic_Curves.o $(OBJECTS_PATH)/Point.o $(OBJECTS_PATH)/Utils.o $(OBJECTS_PATH)/AES.o $(OBJECTS_PATH)/DSA.o
OBJECTS = $(OBJECTS_CRYPTO) $(OBJECTS_PATH)/Main.o $(OBJECTS_PATH)/Network.o $(OBJECTS_PATH)/Security.o $(OBJECTS_PATH)/Log.o $(OBJECTS_PATH)/Security_Client.o

all: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o Jupiter_Test $(LIBRARIES)

$(OBJECTS_PATH)/Main.o: Main.c $(SOURCES_PATH)/Network.h $(SOURCES_PATH)/Log.h
	$(CC) $(CCFLAGS) -c Main.c -o $(OBJECTS_PATH)/Main.o

$(OBJECTS_PATH)/Network.o: $(SOURCES_PATH)/Network.c $(SOURCES_PATH)/Network.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Network.c -o $(OBJECTS_PATH)/Network.o

$(OBJECTS_PATH)/Security.o: $(SOURCES_PATH)/Security.c $(SOURCES_PATH)/Security_Client.h $(SOURCES_PATH)/Network.h $(SOURCES_PATH)/Log.h $(SOURCES_CRYPTO_PATH)/Elliptic_Curves.h $(SOURCES_CRYPTO_PATH)/Point.h $(SOURCES_CRYPTO_PATH)/Utils.h $(SOURCES_CRYPTO_PATH)/AES.h $(SOURCES_CRYPTO_PATH)/DSA.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Security.c -o $(OBJECTS_PATH)/Security.o

$(OBJECTS_PATH)/Log.o: $(SOURCES_PATH)/Log.c $(SOURCES_PATH)/Log.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Log.c -o $(OBJECTS_PATH)/Log.o

$(OBJECTS_PATH)/Security_Client.o: $(SOURCES_PATH)/Security_Client.c $(SOURCES_PATH)/Security_Client.h $(SOURCES_PATH)/Security.h
	$(CC) $(CCFLAGS) -c $(SOURCES_PATH)/Security_Client.c -o $(OBJECTS_PATH)/Security_Client.o

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
	rm -f $(OBJECTS) Jupiter_Test
