#include<stdio.h>
#include<string.h>
#include<vector>
#include<fcntl.h>
#include<unistd.h>
#include"epoll.h"
#include"util.h"
#include"channel.h"
#include"address.h"
#include"socket.h"
#include<errno.h>

#define  MAX_BUFF 1024

void Readevenst(int fd);
int main(){
    Socket *serv_sock = new Socket();
    Inetaddress *serv_addr = new Inetaddress("127.0.0.1",8888);
    serv_sock->bind(serv_addr);
    serv_sock->listen();
    Epoll *ep = new Epoll();
    serv_sock->setblocking();
    channels *serv_channel = new channels (ep ,serv_sock->getfd());
    serv_channel->enablereading();
    while(true){
        std::vector<channels*> activeChannels = ep->poll();
        int nfds = activeChannels.size();
        for(int i = 0;i<nfds;i++){
            int chfd = activeChannels[i]->getfd();
            if(chfd == serv_sock->getfd()){
                Inetaddress *clnt_addr = new Inetaddress();
                Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));
                printf("new client fd %d,ip: %s,htons:%d\n",clnt_sock->getfd(),inet_ntoa(clnt_addr->addr.sin_addr),ntohs(clnt_addr->addr.sin_port));
                clnt_sock->setblocking();
                channels *clntChannel = new channels(ep,clnt_sock->getfd());
                clntChannel->enablereading();
            }
            else if(activeChannels[i]->getrevents() & EPOLLIN){
                Readevenst(activeChannels[i]->getfd());
            }
            else{
                printf("other\n");
            }
        }
    }
}
void Readevenst(int fd){
    char buf[MAX_BUFF];
    while(true){
        bzero(&buf,sizeof(buf));
        ssize_t byte_read = read(fd,buf,sizeof(buf));
        if(byte_read>0){
            printf("message from client fd %d: %s\n", fd, buf);
            write(fd, buf, sizeof(buf));
        }else if(byte_read == -1 &&errno ==EINTR){
            printf("continue reading");
            continue;
        }else if(byte_read == -1&&((errno == EAGAIN) || (errno == EWOULDBLOCK))){
            printf("finish reading once, errno: %d\n", errno);
            break;
        }else if(byte_read == 0){
            printf("EOF ,clientfd %d,disconnect",fd);
            close(fd);
            break;
        }
    }
}
