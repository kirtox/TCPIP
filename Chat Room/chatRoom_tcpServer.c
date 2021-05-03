#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MYPORT 5050

typedef struct sockaddr *sockaddrp;

struct sockaddr_in src_addr[50];
socklen_t src_len = sizeof(src_addr[0]);

int confd[50] = {};
//set number of connection
int count = 0;


void *broadcast(void *indexp)
{
    int index = *(int *)indexp;
    char buf_rcv[255] = {};
    char buf_snd[255] = {};
    char cli_num[2] = {(index+1)+'0'};
    char name[10] = "client";
    strcat(name, cli_num);




    while(1)
    {
        bzero(buf_rcv,sizeof(buf_rcv));
        recv(confd[index],buf_rcv,sizeof(buf_rcv),0);


        if(0 == strcmp("quit",buf_rcv))
        {
            sprintf(buf_snd,"%s exit chat room",name);
            for(int i = 0;i <= count;i++)
            {
                if(i == index || 0 == confd[i])
                {
                    continue;
                }

                send(confd[i],buf_snd,strlen(buf_snd),0);
            }
            confd[index] = -1;
            pthread_exit(0);

        }


        sprintf(buf_snd,"%s:%s",name,buf_rcv);
        printf("%s\n",buf_snd);
        for(int i = 0;i <= count;i++)
        {
            if(i == index || 0 == confd[i])
            {
                continue;
            }

            send(confd[i],buf_snd,sizeof(buf_snd),0);
        }

    }

}




int main(int argc,char **argv)
{
    printf("Chat room is online\n");


    //bulid socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(0 > sockfd)
    {
        perror("socket");
        return -1;
    }

    //prepare address
    struct sockaddr_in addr = {AF_INET};
    addr.sin_port = htons(MYPORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    socklen_t addr_len = sizeof(addr);



    //bind
    int ret = bind(sockfd,(sockaddrp)&addr,addr_len);
    if(0 > ret)
    {
        perror("bind");
        return -1;
    }


    //Set Maximum
    listen(sockfd,50);

    int index = 0;


    while(count <= 50)
    {
        confd[count] = accept(sockfd,(sockaddrp)&src_addr[count],&src_len);
        ++count;
        //Save the client address in convenience of next connection
        index = count-1;

        pthread_t tid;
        int ret = pthread_create(&tid,NULL,broadcast,&index);
        if(0 > ret)
        {

            perror("pthread_create");
            return -1;
        }
        printf("client%d connect\n",index+1);

    }


}
