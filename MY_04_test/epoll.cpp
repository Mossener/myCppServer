#include"epoll.h"
#include"util.h"
#include<unistd.h>
#include<string.h>

#define MAX_EVENT 1000
Epoll::Epoll():epfd(-1),events(nullptr){
    epfd = epoll_create1(0);
    errif(epfd == -1,"epoll create error");
    events = new epoll_event[MAX_EVENT];
    bzero(events,sizeof(*events)*MAX_EVENT);
}
void Epoll::addfd(int fd,uint32_t A){
    struct epoll_event ev;
    bzero(&ev,sizeof(&ev));
    ev.data.fd = fd;
    ev.events = A;
    errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev) == -1,"epoll event add error ");
}
Epoll::~Epoll(){
    if(epfd!=-1){
        close(epfd);
        epfd=-1;
    }
    delete []events;
}
std::vector<epoll_event> Epoll::poll(int time){
    std::vector<epoll_event> activeevents;
    int nfds = epoll_wait(epfd,events,MAX_EVENT,time);
    errif(nfds == -1,"epoll wait error");
    for(int i = 0;i<nfds;i++){
        activeevents.push_back(events[i]);
    }
    return activeevents;
}