#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>

#define MYPORT 5050
#define Server_addr "127.0.0.1"

typedef struct sockaddr *sockaddrp;
int sockfd;

void *recv_other(void *arg)
{
    char buf[255]= {};
    while(1)
    {
        int ret = recv(sockfd,buf,sizeof(buf),0);
        if(0 > ret)
        {
            perror("recv");
            return 0;
        }
        printf("%s\n",buf);
    }
}




int main(int argc,char **argv)
{
    //build socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(0 > sockfd)
    {
        perror("socket");
        return -1;
    }

    //prepare connected address
    struct sockaddr_in addr = {AF_INET};
    addr.sin_port = htons(MYPORT);
    addr.sin_addr.s_addr = inet_addr(Server_addr);

    socklen_t addr_len = sizeof(addr);


    //Connect
    int ret = connect(sockfd,(sockaddrp)&addr,addr_len);
    if(0 > ret)
    {
        perror("connect");
      //  printf("hello"\n", );
        return -1;
    }

    //Send client's name
    char buf[255] = {};


    //Build child thread
    pthread_t tid;
    ret = pthread_create(&tid,NULL,recv_other,NULL);

    if(0 > ret)
    {
        perror("pthread_create");
        return -1;
    }
    //Send in loop
    while(1)
    {
        printf("Type message: \n");
        scanf("%s",buf);
        int ret = send(sockfd,buf,strlen(buf),0);
        if(0 > ret)
        {
            perror("send");
            return -1;
        }

        //Enter quit to exit
        if(0 == strcmp("quit",buf))
        {
            printf("You have already exited chat room.\n");
            return 0;
        }

    }

}
