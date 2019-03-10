#include "client.h"
#include "TCP.h"
#include "UDP.h"

char *MULTICAST_IP = "224.0.0.1";
int MULTICAST_PORT = 9010;

Token global_token;

void signal_exit(int signo) {
  if (strcmp(PROTOCOL, "tcp") == 0) {

  } else { //"udp"
    udp_send_disconnect_token();
    if (HAS_TOKEN == 1) {
      udp_send_token(global_token);
    }
  }
  close(IN_SOCKET);
  close(OUT_SOCKET);
  close(MULTICAST_SOCKET);
  exit(0);
}

void atexit_exit() {
  if (strcmp(PROTOCOL, "tcp")) {

  } else { //"udp"
    udp_send_disconnect_token();
  }
  close(IN_SOCKET);
  close(OUT_SOCKET);
  close(MULTICAST_SOCKET);
}

void init_multicast() {
  if ((MULTICAST_SOCKET = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("Error during init_multicast()\n");
    exit(1);
  }
}

void send_multicast(char *message, int size) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(MULTICAST_IP);
  addr.sin_port = htons(MULTICAST_PORT);

  if (sendto(MULTICAST_SOCKET, message, size, 0, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
    printf("Error during multicast send\n");
    exit(1);
  }
}

int main(int argc, char **argv) {
  srand(time(NULL));

  if (argc == 2 && strcmp(argv[1], "help") == 0) {
    printf("./client <ID> <PORT> <NEXT_IP> <NEXT_PORT> <HAS_TOKEN> <PROTOCOL>\n");
    exit(1);
  }

  if (argc != 7) {
    printf("Invalid argument number. Run ./client help for help\n");
    exit(1);
  }

  ID = argv[1];
  PORT = atoi(argv[2]);
  NEXT_IP = argv[3];
  NEXT_PORT = atoi(argv[4]);
  HAS_TOKEN = atoi(argv[5]);
  PROTOCOL = argv[6];

  if (HAS_TOKEN != 0 && HAS_TOKEN != 1) {
    printf("HAS_TOKEN should be 0 - false or 1 - true\n");
    exit(1);
  }

  if (strcmp(PROTOCOL, "tcp") != 0 && strcmp(PROTOCOL, "udp") != 0) {
    printf("PROTOCOL should be udp or tcp\n");
    exit(1);
  }

  if (atexit(atexit_exit) != 0) {
    printf("Error during atexit()\\n");
  }

  signal(SIGINT, signal_exit);

  printf("Initialized client\n");
  printf("ID = %s\nPORT = %d\nNEXT_IP = %s\nNEXT_PORT = %d\nHAS_TOKEN = %d\nPROTOCOL = %s\n",
   ID, PORT, NEXT_IP, NEXT_PORT, HAS_TOKEN, PROTOCOL);

  init_multicast();

  // initial
  if (strcmp(PROTOCOL, "tcp") == 0) {

  } else { //"udp"
    udp_init_input_socket();
    udp_init_output_socket();

    printf("Initialized sockets\n");

    udp_send_init_token();

    printf("Sent init token\n");

    if (HAS_TOKEN == 1) {
      Token token;
      token.msg_type = DATA;
      token.value = rand() % 100;
      token.taken = rand() % 3 + 3;

      udp_send_token(token);

      printf("Since I HAS_TOKEN, sent token\n");
    }
  }

  // network
  if (strcmp(PROTOCOL, "tcp") == 0) {
    while (1) {

    }
  } else { //"udp"
    while (1) {
      Token token;
      struct sockaddr_in addr;

      recvfrom(IN_SOCKET, &token, sizeof(token), 0, NULL, NULL);

      switch (token.msg_type) {
        case INIT:
          printf("Got INIT token\n");
          if (NEXT_PORT == token.next_port) {
            printf("Remapped\n");
            NEXT_PORT = token.port;
          } else {
            printf("Not my business\n");
            udp_send_token(token);
          }
          break;
        case DATA:
          send_multicast(ID, strlen(ID) * sizeof(char));
          printf("Got DATA token\n");
          if (token.taken == 0) {
            token.value = rand() % 100;
            token.taken = rand() % 3 + 3;
          } else {
            token.taken = token.taken - 1;
          }

          HAS_TOKEN = 1;
          global_token = token;

          sleep(1);

          udp_send_token(token);
          HAS_TOKEN = 0;
          break;
        case DISCONNECT:
          printf("Got DISCONNECT token\n");
          if (NEXT_PORT = token.port) {
            printf("Remapped\n");
            NEXT_PORT = token.next_port;
            udp_init_output_socket();
          } else {
            printf("Not my business\n");
            udp_send_token(token);
          }
          break;
      }
    }
  }

  return 0;
}
