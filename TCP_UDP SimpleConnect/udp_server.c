#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>

#define PortNumber 5555

int main(int argc, char *argv[]) {

    struct timeval start;
    struct timeval end;
    int gettimeofday(struct timeval *tv,struct timezone *tz);
    unsigned long diff;
    struct sockaddr_in address, client_address;
    int sock, byte_recv, byte_sent, client_address_length;
    char buffer[256];
    char buff[9]="welcome\n";
    double throughput;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0)    printf("Error creating socket\n");
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PortNumber);
    address.sin_addr.s_addr = INADDR_ANY;  
   /*#define INADDR_ANY  ((unsigned long int) 0x00000000) 
      INADDR_ANY allows the server to accept a client connection on any interface, in case the server host has multiple interfaces.*/
    if (bind(sock,(struct sockaddr *)&address, sizeof(address)) == -1) {
        printf("error binding\n");
        close(sock);}
	//int address_length = sizeof(address); 
	client_address_length = sizeof(client_address);
    while(1){
	bzero(buffer,256);
        byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr    
             *)&client_address, &client_address_length);
	gettimeofday(&end,NULL);
        if (byte_recv < 0)    printf("Error recving packet\n");
	//receive time from client
	byte_recv = recvfrom(sock, (struct timeval *)&start, sizeof(start), 0, (struct sockaddr
             *)&client_address, &client_address_length);
	if (byte_recv < 0)    printf("Error recving time_packet\n");
	printf("Received packet: %s\n",buffer);
	
	diff = 1000000 * (end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec;
	printf("Time: %ld(ms)\n",diff);
	
	throughput = sizeof(buffer)/((double)diff);
	printf("Throughput: %lf (MB/s)",throughput);
	printf("\n");
	//send welcome to client
	byte_sent =  sendto(sock,buff, sizeof(buff), 0, (struct sockaddr *)&client_address, client_address_length);
	if (byte_sent < 0)    printf("Error sending packet\n");
	
    } 
}
