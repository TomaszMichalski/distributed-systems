#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

char *MULTICAST_IP;
int MULTICAST_PORT;

int IN_SOCKET;
int OUT_SOCKET;
int MULTICAST_SOCKET;
int TCP_IN_SOCKET;

char *ID;
int PORT;
char *NEXT_IP;
int NEXT_PORT;
int HAS_TOKEN;
char *PROTOCOL;

typedef enum {
  INIT,
  DATA,
  DISCONNECT
} MSG_TYPE;

typedef struct {
  MSG_TYPE msg_type;
  int value;
  int taken;
  int port;
  int next_port;
} Token;

#endif
