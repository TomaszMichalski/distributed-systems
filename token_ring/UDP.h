#ifndef UDP_H
#define UDP_H

#include "client.h"

void udp_init_input_socket();
void udp_init_output_socket();
void udp_send_token(Token token);
void udp_send_init_token();
void udp_send_disconnect_token();

#endif
