#ifndef SOCKET_H
#define SOCKET_H
#include"address.h"

class Socket{
private:
    int sockfd;
public:
    Socket();
    Socket(int fd);
    ~Socket();

    void bind(Inetaddress*A);
    void listen();
    void setblocking();

    int accept(Inetaddress*A);
    int getfd();
};
#endif