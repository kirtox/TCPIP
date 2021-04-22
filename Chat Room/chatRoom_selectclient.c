#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <resolv.h>

#define PORT 5050
#define Server_addr "127.0.0.1"

#define MAXBUF 1024
int main(int argc,char **argv){
    int sockfd,len;
    struct sockaddr_in dest;
    char buffer[MAXBUF+1];
    fd_set rfds;
    struct timeval tv;
    int retval,maxfd = -1;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        exit(errno);
    }


    bzero(&dest,sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    if(inet_aton(Server_addr,(struct in_addr *)&dest.sin_addr.s_addr) == 0){
        perror(Server_addr);
        exit(errno);
    }

    /*conect to the server*/
    if(connect(sockfd,(struct sockaddr*)&dest,sizeof(dest)) !=0){
        perror("connect");
        exit(errno);
    }

    //printf("\n---ready to chatting...---\n");
    printf("Type message:\n");
    while(1){

        FD_ZERO(&rfds);

        FD_SET(0,&rfds);
        maxfd = 0;

        FD_SET(sockfd,&rfds);
        if(sockfd > maxfd)
            maxfd = sockfd;

        tv.tv_sec = 60;
        tv.tv_usec = 0;

        retval = select(maxfd+1,&rfds,NULL,NULL,&tv);

        if(retval == -1){
            printf("select error,quit!\n");
            break;
        }else if(retval == 0){
            printf("idle message\n");
            continue;
        }else{
            if(FD_ISSET(sockfd,&rfds)){

                bzero(buffer,MAXBUF+1);

                len = recv(sockfd, buffer, MAXBUF, 0);
                if(len > 0)
                    printf("%s\n ",buffer);
                else{
                    if(len < 0){
                        printf("recv msg fail.the errno is:%d,error info is %s.\n",errno,strerror(errno));
                    }
                    else
                        printf("quit.\n");
                    break;
                }
            }
            if(FD_ISSET(0,&rfds)){

                bzero(buffer, MAXBUF+1);

                fgets(buffer, MAXBUF, stdin);
                if(!strncasecmp(buffer, "quit", 4)){
                    printf("self request to quit the chating\n");
                    break;
                }

                len = send(sockfd, buffer, strlen(buffer)-1 , 0);
                if(len < 0){
                    printf("mgs:%s send fail!errno is:%d,error info is:%s\n", buffer, errno, strerror(errno));
                    break;
                }else{
                    //printf("%s", buffer);
                }
            }

        }

    }

    close(sockfd);
    return 0;
}
