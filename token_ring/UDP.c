#include "UDP.h"

void udp_init_input_socket() {
  if ((IN_SOCKET = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("Error during udp_init_input_socket\n");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(PORT);

  if (bind(IN_SOCKET, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    printf("Error during bind\n");
    exit(1);
  }
}

void udp_init_output_socket() {
  if ((OUT_SOCKET = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("Error during udp_init_output_socket\n");
    exit(1);
  }
}

void udp_send_token(Token token) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(NEXT_IP);
  addr.sin_port = htons(NEXT_PORT);

  if (sendto(OUT_SOCKET, &token, sizeof(token), 0, (const struct sockaddr *) &addr, sizeof(addr)) != sizeof(token)) {
    printf("Error during send token\n");
    exit(1);
  }
}

void udp_send_init_token() {
  Token token;
  token.msg_type = INIT;
  token.next_port = NEXT_PORT;
  token.port = PORT;

  udp_send_token(token);
}

void udp_send_disconnect_token() {
  Token token;
  token.msg_type = DISCONNECT;
  token.next_port = NEXT_PORT;
  token.port = PORT;

  udp_send_token(token);
}
