#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

unsigned short checksum(unsigned short *buffer, int buffer_size){
    unsigned long sum = 0xffff;

    while(buffer_size > 1){
        sum += *buffer;
        buffer++;
        buffer_size -= 2;
    }

    if(buffer_size == 1)
        sum += *(unsigned char*)buffer;

    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("IP_address: %s !\n", argv[0]);
        exit(-1);
    }

    int sd, rd, sock, inet, sequence=0;
    char buffer[1024];
    double max_rtt=0, min_rtt=1000, avg_rtt=0, ms_rtt;
    unsigned long rtt;

    struct timeval start, end;
    struct sockaddr_in addr;
    struct icmp *icmp_pointer;
    struct iphdr *ip_hdr_pointer;
    struct icmp icmp;
    //struct icmphdr icmp_hdr;
    //struct icmphdr *icmp_hdr_pointer;

    //ipv4: PF_INET
    addr.sin_family = PF_INET;

    inet = inet_pton(PF_INET, argv[1], &addr.sin_addr);
    if(inet < 0){
        perror("Error: inet!");
        exit(-1);
    }

    sock = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sock < 0){
        perror("Error: sock!");
        exit(-1);
    }

    //memset(&icmp_hdr, 0, sizeof(icmp_hdr));
    memset(&icmp, 0, sizeof(icmp));
    //printf("test");
    icmp.icmp_type = ICMP_ECHO;
    icmp.icmp_code = 0;
    icmp.icmp_cksum = checksum((unsigned short*)&icmp, sizeof(icmp));
    //icmp_hdr.type = ICMP_ECHO;
    //icmp_hdr.code = 0;
    //icmp_hdr.checksum = checksum((unsigned short*)&icmp_hdr, sizeof(icmp_hdr));
    //printf("before while");
    while(sequence<10){
      //get start time
      gettimeofday(&start, NULL);

      //inet = sendto(sock, (char*)&icmp_hdr, sizeof(icmp_hdr), 0, (struct sockaddr*)&addr, sizeof(addr));
      sd = sendto(sock, (char*)&icmp, sizeof(icmp), 0, (struct sockaddr*)&addr, sizeof(addr));
      //printf("sd: %d\n",sd);
      if(sd < 1){
          perror("Error: sd");
          exit(-1);
      }

      memset(buffer, 0, sizeof(buffer));

      rd = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
      //get end time
      gettimeofday(&end, NULL);
      sequence++;

      if(rd < 1){
          perror("recv");
          exit(-1);
      }
      //icmp_hdr pointer
      ip_hdr_pointer = (struct iphdr*)buffer;
      //icmp_hdr_pointer = (struct icmphdr*)(buffer + (ip_hdr_pointer->ihl) * 4);
      icmp_pointer = (struct icmp*)(buffer + (ip_hdr_pointer->ihl) * 4);
      //RTT = end - start;
      rtt =  1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
      ms_rtt = (double)rtt/1000;

      //get max & min rtt
      if(max_rtt < ms_rtt) max_rtt=ms_rtt;
      if(min_rtt > ms_rtt) min_rtt=ms_rtt;

      avg_rtt += ms_rtt;

      //print ping result
      printf("replyfrom = %s, ", argv[1]);
      printf("icmp_type = %d, ", icmp_pointer->icmp_type);
      printf("icmp_code = %d, ", icmp_pointer->icmp_type);
      printf("icmp_seq = %d, ", sequence);
      printf("RTT: %.2lfms\n", ms_rtt);
    }

    avg_rtt = avg_rtt/sequence;
    printf("\nMax RTT: %.2lfms,  Min RTT: %.2lfms,  Avg RTT: %.2lfms\n", max_rtt, min_rtt, avg_rtt);
    close(sock);

    return 0;
}
