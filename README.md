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
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Chat%20Room/tcpServer.png?raw=true)
		- ```./chatRoom_tcpClient```
		- Add two clients
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Chat%20Room/tcpClient1.png?raw=true)
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Chat%20Room/tcpClient2.png?raw=true)

## **Create a chat room by using TCP protocol with Select()**

- **Server/Client**
	- Compile
		- ```gcc -o chatRoom_selectServer chatRoom_selectServer.c```
		- ```gcc -o chatRoom_selectClient chatRoom_selectClient.c```
	- Run
		- ```./chatRoom_selectClient```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Chat%20Room/selectServer.png?raw=true)
		- ```./chatRoom_selectClient```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Chat%20Room/selectClient1.png?raw=true)
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Chat%20Room/selectClient2.png?raw=true)

***

# ICMP Message Processing

## **Create a ping program**

- **Ping**
	- Compile
		- ```gcc -o ping ping.c```
	- Run
		- ```./ping```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/ICMP%20Message%20Processing/ping.png?raw=true)

***

# Packet Capture

- **Capture 200 ICMP packets**
	- Compile
		- ```gcc -o packet_capture_1 packet_capture_1.c```
	- Run
		- ```./packet_capture_1```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Packet%20Capture/packet_capture_1.png?raw=true)

- **Capture 5 UDP packets (Destination belongs to me)**
	- Compile
		- ```gcc -o packet_capture_2 packet_capture_2.c```
	- Run
		- ```./packet_capture_2```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Packet%20Capture/packet_capture_2.png?raw=true)
	- Check
		- by wireshark
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Packet%20Capture/udpWireshark.png?raw=true)


- **Capture 5 TCP packets (Source or destination not belong to me)**
	- Compile
		- ```gcc -o packet_capture_3 packet_capture_3.c```
	- Run
		- ```./packet_capture_3```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Packet%20Capture/packet_capture_3.png?raw=true)
	- Check
		- by wireshark
		- ![image](https://github.com/kirtox/TCPIP/blob/main/Packet%20Capture/tcpWireshark.png?raw=true)

***

# TCP_UDP SimpleConnect

- ## **Using UDP socket**
	- Compile
		- ```gcc -o udp_server udp_server.c```
		- ```gcc -o udp_client udp_client.c```
	- Run
		- ```./udp_server```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/TCP_UDP%20SimpleConnect/udpServer.png?raw=true)
		- ```./udp_client```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/TCP_UDP%20SimpleConnect/udpClient.png?raw=true)


- ## **Using UDP socket**
	- Compile
		- ```gcc -o tcp_server tcp_server.c```
		- ```gcc -o tcp_client tcp_client.c```
	- Run
		- ```./tcp_server```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/TCP_UDP%20SimpleConnect/tcpServer.png?raw=true)
		- ```./tcp_client```
		- ![image](https://github.com/kirtox/TCPIP/blob/main/TCP_UDP%20SimpleConnect/tcpClient.png?raw=true)

***

