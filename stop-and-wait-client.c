#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

typedef struct packet {
	char data[1024];
} Packet;

typedef struct frame {
	int frame_kind; // ACK:0, SEQ:1, FIN:2
	int sq_no;
	int ack;
	Packet packet;
} Frame;

int main() {
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = 6969;
	server.sin_addr.s_addr = INADDR_ANY;
	int frame_id = 0, ack_recv = 1;
	Frame frame_send, frame_recv;
	char buf[100];
	while(1) {
		if (ack_recv == 1) {
			frame_send.frame_kind = 1;
			frame_send.sq_no = frame_id;
			frame_send.ack = 0;
			printf("Enter Data : ");
			fgets(buf, 100, stdin);
			strcpy(frame_send.packet.data, buf);
			sendto(sd, &frame_send, sizeof(frame_send), 0, (struct sockaddr *) &server, sizeof(server));
			printf("[+] Frame sent\n");
		}
		int len = sizeof(server);
		int k = recvfrom(sd, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr *) &server, &len);
		if (k > 0 && frame_recv.sq_no==0 && frame_recv.ack==frame_id+1) {
			printf("[+] Ack Received\n");
			ack_recv = 1;
		} else {
			printf("[-] Ack Not Received\n");
			ack_recv = 0;
		}
		frame_id++;
	}
	close(sd);
	return 0;
}

