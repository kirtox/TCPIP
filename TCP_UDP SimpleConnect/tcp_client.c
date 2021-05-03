#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define Server_PortNumber 7070
#define Server_Address "127.0.0.1"

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr, client_addr;
    int sock, recfd, byte_sent, byte_recv, server_addr_length = sizeof(server_addr), client_addr_length=sizeof(client_addr);
    //char buff[9]="welcome\n";
    char buffer[256];

    struct timeval start;
    struct timeval end;
    unsigned long diff;
    //int gettimeofday(struct timeval *tv, struct timezone *tz);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)    printf("Error creating socket!\n");

    bzero(&server_addr, server_addr_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(Server_PortNumber);
    server_addr.sin_addr.s_addr = inet_addr(Server_Address);

    if (connect(sock, (struct sockaddr *)&server_addr,server_addr_length)==-1) {
        printf("connect failed!");
        close(sock);}


    while(1){
	printf("Packet content: ");
    	fgets(buffer,sizeof(buffer),stdin);
	byte_sent = send(sock, buffer, sizeof(buffer),0);
        gettimeofday(&start,NULL);
	if (byte_sent < 0)    printf("Error sending packet!\n");

	byte_sent = send(sock, (struct timeval *)&start, sizeof(start),0);
        if (byte_sent < 0)    printf("Error sending time_packet!\n");

	byte_recv = recv(sock, buffer, sizeof(buffer),0);
	if (byte_recv < 0)	printf("Error recving packet\n");
	printf(buffer);   
    	printf("\n");
    }
 
    close(sock);
    return 0;
    
}
