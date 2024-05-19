#include<stdio.h>
#include"socket.h"
#include"address.h"
#include"util.h"
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>

#define BUFF_MAX 1024
int main(){
    Socket *serv_sock = new Socket();
    Inetaddress* serv_addr = new Inetaddress("127.0.0.1",8888);
    errif(connect(serv_sock->getfd(),(sockaddr*)&serv_addr->addr,sizeof(serv_addr->addr)),"server connect error");
    while(true){
        char buf[BUFF_MAX];
        bzero(&buf,sizeof(BUFF_MAX));
        scanf("%s",buf);
        ssize_t write_bytes = write(serv_sock->getfd(),buf,sizeof(buf));
        if(write_bytes == -1){
            printf("sockfd already disconnect\n");
            break;
        }
        bzero(&buf,sizeof(buf));
        ssize_t read_bytes = read(serv_sock->getfd(),buf,sizeof(buf));
        if(read_bytes>0){
            printf("message from server %s\n",buf);
        }
        else if(read_bytes == 0){
            printf("socket disconneted\n");
        }
        else if(read_bytes == -1){
            close(serv_sock->getfd());
            errif(true,"socket read error");
        }
    } 
    close(serv_sock->getfd());
    return 0;
}
