#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <linux/udp.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>

int main()
{
	int sock_addr_size, rd;
	int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	//memory allocation
	unsigned char *buffer = (unsigned char *) malloc(65536);

	struct ifreq ifr;
	struct sockaddr sock_addr;

	printf("---------------Start---------------\n");
	//copy part of string, IFNAMSIZ=>len
	strncpy(ifr.ifr_name, "enp2s0", IFNAMSIZ);
	//get original flag
	if(ioctl(sock, SIOCGIFFLAGS, &ifr) == -1){
		perror("Error: ioctl!!!");
		exit(1);
	}
	ifr.ifr_flags |= IFF_PROMISC;
	//set
	if(ioctl(sock, SIOCSIFFLAGS, &ifr) == -1){
		perror("Error: ioctl!!!");
		exit(1);
	}

	for(int count=0 ; count<5 ; )
	{
		unsigned short ip_len;
		struct sockaddr_in src, dst;
		struct ether_header *ether = (struct ether_header *)buffer;
		struct iphdr *ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
		
		//get size of sock_addr
		sock_addr_size = sizeof(sock_addr);

		//Receive packet
		rd = recvfrom(sock, buffer, 65536, 0, &sock_addr, (socklen_t*)&sock_addr_size);
		if(rd < 0)
		{
			perror("Error: recvfrom!!!\n");
			exit(1);
		}
		//like bzero
		memset(&src, 0, sizeof(src));
		memset(&dst, 0, sizeof(dst));
		src.sin_addr.s_addr = ip->saddr;
		dst.sin_addr.s_addr = ip->daddr;

		ip_len = ip->ihl * 4;
		struct udphdr *udp_hdr = (struct udphdr*)(buffer + ip_len + sizeof(struct ethhdr));
		//printf("test\n");

		//only get UDP packet & check ip address by using strcmp
		if(ip->protocol == IPPROTO_UDP && strcmp(inet_ntoa(dst.sin_addr), "140.120.15.176") == 0)
		{
			printf("packet %d:\n", count+1);
			printf("Source MAC address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", ether->ether_shost[0], ether->ether_shost[1], ether->ether_shost[2], ether->ether_shost[3], ether->ether_shost[4], ether->ether_shost[5]);
			printf("Destination MAC address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", ether->ether_dhost[0], ether->ether_dhost[1], ether->ether_dhost[2], ether->ether_dhost[3], ether->ether_dhost[4], ether->ether_dhost[5]);
			printf("IP->protocol            = UDP\n");
			printf("IP->src_ip              = %s\n", inet_ntoa(src.sin_addr));
			printf("IP->dst_ip              = %s\n", inet_ntoa(dst.sin_addr));
			printf("Src_port                = %d\n", ntohs(udp_hdr->source));
			printf("Dst_port                = %d\n", ntohs(udp_hdr->dest));
			printf("=================================================================\n");
			count++;
		}
	}
	close(sock);
	printf("---------------finish--------------\n");

	//close, or it will open forever
	ifr.ifr_flags &= ~IFF_PROMISC;
	ioctl(sock, SIOCGIFFLAGS, &ifr);

	return 0;
}
