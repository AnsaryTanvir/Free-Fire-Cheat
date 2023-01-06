#ifndef CONST_H
#define CONST_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <vector>
#include <errno.h>
#include <stdio.h>
#include <sys/un.h>

#define SOCKET_NAME "\0pgkserver"
#define BACKLOG 8
#define PacketSize 4096

#endif
