#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>
#include"util.h"
#include"socket.h"
#include"address.h"
Socket::Socket():sockfd(-1){
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    errif(sockfd == -1 ,"socket create error");
}

Socket::Socket(int fd):sockfd(fd){
    errif(sockfd == -1 ,"socket create error");
}

void Socket::bind(Inetaddress* A ){
    errif(::bind(sockfd,(sockaddr*)&A->addr,A->addr_len) == -1,"socket bind error");
}
void Socket::listen(){
    errif(::listen(sockfd,SOMAXCONN) == -1,"socket listen error");
}
void Socket::setblocking(){
    fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL) | O_NONBLOCK);
}

int Socket::accept(Inetaddress*A){
    int tempfd = ::accept(sockfd,(sockaddr*)&A->addr,&A->addr_len);
    errif(tempfd == -1,"socket accept error");
    return tempfd;
}
int Socket::getfd(){
    return sockfd;
}
Socket::~Socket(){
    if(sockfd != -1){
        close(sockfd);
        sockfd = -1;
    }
}