#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
int main() {
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		printf("Error in socket()");
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 6969;
	int k = bind(sd, (struct sockaddr*) &server, sizeof(server));
	if (k == -1) {
		printf("Error in bind()");
	}
	char buf[100];
	int len = sizeof(server);
	k = recvfrom(sd, buf, 100, 0, (struct sockaddr*) &server, &len);
	if (k < 0) {
		printf("Error in recvfrom()");
	}
	printf("Message from client : %s", buf);
	printf("Enter message to send to client : ");
	fgets(buf, 100, stdin);
	k = sendto(sd, buf, 100, 0, (struct sockaddr*) &server, sizeof(server));
	if (k < 0) {
		printf("Error in sendto()");
	}
	return 0;
}
