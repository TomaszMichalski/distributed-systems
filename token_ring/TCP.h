#ifndef TCP_H
#define TCP_H

#include "client.h"

void tcp_init_input_socket();
void tcp_init_output_socket();
void tcp_accept();
void tcp_connect();
void tcp_send_token(Token token);
void tcp_send_init_token();
void tcp_send_disconnect_token();

#endif
