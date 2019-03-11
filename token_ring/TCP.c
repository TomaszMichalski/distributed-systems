#include "TCP.h"

void tcp_init_input_socket() {
  if ((IN_SOCKET = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("Error during tcp init input socket\n");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(PORT);

  if (bind(IN_SOCKET, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
    printf("Error during bind\n");
    exit(1);
  }

  if (listen(IN_SOCKET, 10) != 0) {
    printf("Error during listen\n");
    exit(1);
  }
}

void tcp_init_output_socket() {
  if ((OUT_SOCKET = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("Error during tcp init output socket\n");
    exit(1);
  }
}

void tcp_accept() {
  if ((TCP_IN_SOCKET = accept(IN_SOCKET, NULL, NULL)) == -1) {
    printf("Error during tcp accept\n");
    exit(1);
  }
}

void tcp_connect() {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(NEXT_PORT);

  if (connect(OUT_SOCKET, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    printf("Error during tcp connect\n");
    exit(1);
  }
  usleep(500000);
}

void tcp_send_token(Token token) {
  tcp_init_output_socket();
  tcp_connect();
  write(OUT_SOCKET, &token, sizeof(token));
  close(OUT_SOCKET);
}

void tcp_send_init_token() {
  Token token;
  token.msg_type = INIT;
  token.next_port = NEXT_PORT;
  token.port = PORT;

  tcp_send_token(token);
}

void tcp_send_disconnect_token() {
  Token token;
  token.msg_type = DISCONNECT;
  token.next_port = NEXT_PORT;
  token.port = PORT;

  tcp_send_token(token);
}
