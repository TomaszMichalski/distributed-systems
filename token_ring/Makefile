CC=gcc
OPT=-Wall
LIB=-pthread

all: client.o TCP.o UDP.o
	$(CC) $(OPT) client.o UDP.o TCP.o -o client $(LIB)
tcp: TCP.c TCP.h client.h
	$(CC) $(OPT) TCP.c -o TCP.o $(LIB)
udp: UDP.c UDP.h client.h
	$(CC) $(OPT) UDP.c -o UDP.o $(LIB)
client: client.c client.h
	$(CC) $(OPT) client.c -o client.o $(LIB)
clean:
	rm -f *.o client
	make all
