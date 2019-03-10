#!/usr/bin/env python3

import struct
import socket
import datetime

MULTICAST_IP = "224.0.0.1"
MULTICAST_PORT = 9010
buff = []

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

sock.bind((MULTICAST_IP, MULTICAST_PORT))

mreq = struct.pack("4sl", socket.inet_aton(MULTICAST_IP), socket.INADDR_ANY)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

while True:
    buff = sock.recv(1024)
    print("%s | %s\n" % (str(datetime.datetime.now())[:-7], buff.decode('utf-8')))
