#include"epoll.h"
#include"util.h"
#include"channel.h"
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
std::vector<channels*> Epoll::poll(int time){
    std::vector<channels*> activeevents;
    int nfds = epoll_wait(epfd,events,MAX_EVENT,time);
    errif(nfds == -1,"epoll wait error");
    for(int i = 0;i<nfds;i++){
        channels *ch=(channels*)events[i].data.ptr;
        ch->setrevents(events[i].events);
        activeevents.push_back(ch);
        }
    return activeevents;
}
void Epoll::UcA(channels*ch){
    int fd = ch->getfd();
    struct epoll_event ev ;
    bzero(&ev,sizeof(ev));
    ev.events =  ch->getevents();
    ev.data.ptr = ch;
    if(!ch->getInEpoll()){
        errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev) == -1,"epoll add error");
        ch->getInEpoll();
    }
    else{
        errif(epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev) == -1,"epoll modify error");
    }
}