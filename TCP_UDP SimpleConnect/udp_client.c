#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //for bzero()
#include <unistd.h>  //for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/time.h>

#define Server_PortNumber 5555
#define Server_Address "127.0.0.1"
//140.120.15.242

int main(int argc, char *argv[]) {
    
    struct timeval start;
    struct timeval end;
    //int gettimeofday(struct timeval *tv,struct timezone *tz);

    struct sockaddr_in address;
    int sock, byte_sent ,byte_recv;
    char buffer[256];
    //char buff[7];
	sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0)    printf("Error creating socket\n");

    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(Server_PortNumber);
    address.sin_addr.s_addr = inet_addr(Server_Address);
    int address_length = sizeof(address);
    for(;;){
    	printf("Packet content: ");
    	bzero(buffer,256);
    	fgets(buffer,255,stdin);

    	byte_sent = sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, address_length);
    	
	gettimeofday(&start,NULL);
	if (byte_sent < 0)    printf("Error sending packet\n");
	//send time to server
	byte_sent = sendto(sock, (struct timeval *)&start, sizeof(start), 0, (struct sockaddr *)&address, address_length);
    	if (byte_sent < 0)    printf("Error sending time_packet\n");
	
	byte_recv = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, &address_length);
    	if (byte_recv < 0)    printf("Error recving packet\n");
	printf(buffer);
    	printf("\n");	
    }
    close(sock);
    return 0;
}
