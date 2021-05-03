# **Programs using TCP/UDP packets**

***

# Chat Room

## **Create a chat room by using TCP protocol with Thread**

- **Server/Client**
	- Compile
		- ```gcc -o chatRoom_tcpServer chatRoom_tcpServer.c```
		- ```gcc -o chatRoom_tcpClient chatRoom_tcpClient.c```
	- Run
		- ```./chatRoom_tcpServer```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Chat%20Room/tcpServer.png)
		- ```./chatRoom_tcpClient```
		- Add two clients
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Chat%20Room/tcpClient1.png)
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Chat%20Room/tcpClient2.png)

## **Create a chat room by using TCP protocol with Select()**

- **Server/Client**
	- Compile
		- ```gcc -o chatRoom_selectServer chatRoom_selectServer.c```
		- ```gcc -o chatRoom_selectClient chatRoom_selectClient.c```
	- Run
		- ```./chatRoom_selectClient```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Chat%20Room/selectServer.png)
		- ```./chatRoom_selectClient```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Chat%20Room/selectClient1.png)
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Chat%20Room/selectClient2.png)

***

# ICMP Message Processing

## **Create a ping program**

- **Ping**
	- Compile
		- ```gcc -o ping ping.c```
	- Run
		- ```./ping```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/ICMP%20Message%20Processing/ping.png)

***

# Packet Capture

- **Capture 200 ICMP packets**
	- Compile
		- ```gcc -o packet_capture_1 packet_capture_1.c```
	- Run
		- ```./packet_capture_1```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Packet%20Capture/packet_capture_1.png)

- **Capture 5 UDP packets (Destination belongs to me)**
	- Compile
		- ```gcc -o packet_capture_2 packet_capture_2.c```
	- Run
		- ```./packet_capture_2```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Packet%20Capture/packet_capture_2.png)
	- Check
		- by wireshark
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Packet%20Capture/udpWireshark.png)


- **Capture 5 TCP packets (Source or destination not belong to me)**
	- Compile
		- ```gcc -o packet_capture_3 packet_capture_3.c```
	- Run
		- ```./packet_capture_3```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Packet%20Capture/packet_capture_3.png)
	- Check
		- by wireshark
		- ![image](https://github.com/kirtox/TCPIP/tree/main/Packet%20Capture/tcpWireshark.png)

***

# TCP_UDP SimpleConnect

- ## **Using UDP socket**
	- Compile
		- ```gcc -o udp_server udp_server.c```
		- ```gcc -o udp_client udp_client.c```
	- Run
		- ```./udp_server```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/TCP_UDP%20SimpleConnect/udpServer.png)
		- ```./udp_client```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/TCP_UDP%20SimpleConnect/udpClient.png)


- ## **Using UDP socket**
	- Compile
		- ```gcc -o tcp_server tcp_server.c```
		- ```gcc -o tcp_client tcp_client.c```
	- Run
		- ```./tcp_server```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/TCP_UDP%20SimpleConnect/tcpServer.png)
		- ```./tcp_client```
		- ![image](https://github.com/kirtox/TCPIP/tree/main/TCP_UDP%20SimpleConnect/tcpClient.png)

***

