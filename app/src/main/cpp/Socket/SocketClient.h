#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include "Const.h"

class SocketClient {
public:
    int sockfd;
    sockaddr_un addr_server;
    char socket_name[108]; // 108 sun_path length max
    bool created,connected;

    SocketClient();

    bool Create();
    bool Connect();
    void Close();

    int sendData(void *inData, size_t size);
    bool send(void* inData, size_t size);

    int recvData(void *outData, size_t size);
    size_t receive(void* outData);
};

#endif //SOCKETCLIENT_H
