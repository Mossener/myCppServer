#include<sys/epoll.h>
#include"channel.h"
#include"epoll.h"

channels::channels(Epoll *_ep,int socket):ep(_ep),fd(socket),events(0),revents(0),inEpoll(false){

}
channels::~channels(){

}
void channels::enablereading(){
    events = EPOLLIN | EPOLLET;
    ep->UcA(this);
}

int channels::getfd(){return fd;}

Epoll* channels::getep(){return ep;}

uint32_t channels::getevents(){return events;}

uint32_t channels::getrevents(){return revents;}

bool channels::getInEpoll(){return inEpoll;}
void channels::setrevents(uint32_t RE){revents = RE;}
void channels::setInEpoll(){inEpoll = true;}

