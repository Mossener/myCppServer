#ifndef EPOLL_H
#define EPOLL_H
#include<sys/epoll.h>
#include<vector>

class Epoll{
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();
    ~Epoll();
    
    void addfd(int fd,uint32_t op);
    std::vector<epoll_event> poll(int timeout = -1);
};
#endif