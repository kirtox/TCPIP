#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <linux/ip.h>

int ip_counter=0, arp_counter=0, rarp_counter=0, tcp_counter=0, udp_counter=0, icmp_counter=0, igmp_counter=0;

int main(int argc, char *argv[]){
	int sock_addr_size, rd;
	int sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	unsigned char buffer[ETH_FRAME_LEN];

	struct ifreq ifr;
	struct sockaddr sock_addr;
	struct ether_header *ether = (struct ether_header *)buffer;
	struct iphdr *ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));

	//ubuntu: enp2s0
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

	printf("---------------Statistics---------------\n");
	for(int i=0 ; i<200 ; i++){
		sock_addr_size = sizeof(sock_addr);
		rd = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
		if(rd < 0){
			perror("Error: recvfrom!!!\n");
			exit(1);
		}

		switch (ntohs(ether->ether_type))
		{
			case 0x0800:
				ip_counter++;
				break;

			case 0x0806:
				arp_counter++;
				break;

			case 0x8035:
				rarp_counter++;
				break;

			default:
				break;
		}
		switch (ip->protocol)
		{
			case IPPROTO_TCP:
				tcp_counter++;
				break;

			case IPPROTO_UDP:
				udp_counter++;
				break;

			case IPPROTO_ICMP:
				icmp_counter++;
				break;

			case IPPROTO_IGMP:
				igmp_counter++;
				break;

			default:
				break;
		}
	}
	//print result
	printf("IP      : %d\n", ip_counter);
	printf("ARP     : %d\n", arp_counter);
	printf("RARP    : %d\n", rarp_counter);
	printf("TCP     : %d\n", tcp_counter);
	printf("UDP     : %d\n", udp_counter);
	printf("ICMP    : %d\n", icmp_counter);
	printf("IGMP    : %d\n", igmp_counter);
	close(sock);
	printf("----------------finish----------------\n");
	
	//close, or it will open forever
	ifr.ifr_flags &= ~IFF_PROMISC;
	ioctl(sock, SIOCGIFFLAGS, &ifr);

	return 0;
}
