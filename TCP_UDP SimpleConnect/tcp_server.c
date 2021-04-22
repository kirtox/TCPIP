#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define PortNumber 7070

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr,client_addr;

    struct timeval start;
    struct timeval end;
    unsigned long diff;
    int gettimeofday(struct timeval *tv, struct timezone *tz);

    int sock, byte_recv, byte_sent, server_addr_length = sizeof(server_addr), client_addr_length=sizeof(client_addr), recfd;
    double throughput; 
    char buffer[256];
    char buff[9]="welcome\n";
    unsigned int size;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) printf("Error creating socket\n");

    bzero(&server_addr, server_addr_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PortNumber);
    server_addr.sin_addr.s_addr = INADDR_ANY;  
   /*#define INADDR_ANY  ((unsigned long int) 0x00000000) 
      INADDR_ANY allows the server to accept a client connection on any interface, in case the server host has multiple interfaces.*/

    if (bind(sock,(struct sockaddr *)&server_addr, server_addr_length) == -1) {
    	printf("error binding!\n");
    	close(sock);}
    
    if (listen(sock, 20) == -1) {
    	printf("listen failed!\n");
    	close(sock);}

    if((recfd = accept(sock,(struct sockaddr *)&client_addr,&client_addr_length))==-1) {
    	printf("accept failed!\n");
    	close(sock);}
    
    while(1){
  	byte_recv = recv(recfd, buffer, sizeof(buffer),0);
  	gettimeofday(&end,NULL);
	size = sizeof(buffer);
	if (byte_recv < 0)	printf("Error recving packet\n");
  	printf("Received packet: %s\n",buffer);
	
	byte_recv = recv(recfd,  (struct timeval *)&start, sizeof(start), 0);
        if (byte_recv < 0)      printf("Error recving time_packet\n");


	diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
	printf("Time: %ld (ms)\n",diff);
	//printf("%u\n",size);
	
	throughput = sizeof(buffer)/((double)diff);
	printf("Throughput: %lf (MB/s)",throughput);
	printf("\n");

	byte_sent = send(recfd, buff, sizeof(buff),0);
	if (byte_sent < 0)	printf("Error sending packet\n");
    }
  
}
