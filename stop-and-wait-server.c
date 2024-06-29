#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

typedef struct packet {
	char data[1024];
} Packet;

typedef struct frame {
	int frame_kind; // ACK:0, SEQ:1, FIN:2
	int sq_no;
	int ack;
	Packet packet;
} Frame;

int main () {
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = 6969;
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sd, (struct sockaddr *) &server, sizeof(server));
	int frame_id = 0, len = sizeof(client);
	Frame frame_recv, frame_send;
	while(1) {
		int k = recvfrom(sd, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr *) &client, &len);
		if (k > 0 && frame_recv.frame_kind==1 && frame_recv.sq_no==frame_id) {
			printf("[+]Frame Received: %s",frame_recv.packet.data);
			frame_send.frame_kind = 0;
			frame_send.sq_no = 0;
			frame_send.ack = frame_recv.sq_no + 1;
			sendto(sd, &frame_send, sizeof(frame_send), 0, (struct sockaddr *) &client, len);
			printf("[+]Ack Send\n");
		} else {
			printf("[-] Frame Not Received\n");
		}
		frame_id++;
	}
	close(sd);
	return 0;
}
