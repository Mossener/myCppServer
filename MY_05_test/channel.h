#pragma once 
#include<sys/epoll.h>

class Epoll;
class channels{
private:
    int fd;
    Epoll* ep;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;
public:
    channels (Epoll *ep1,int sockfd);
    ~channels();

    void enablereading();

    int getfd();
    Epoll* getep();
    uint32_t getevents();
    uint32_t getrevents();

    bool getInEpoll();
    void setInEpoll();

    void setrevents(uint32_t RE);
};