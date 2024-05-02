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
	char buf[100];
	printf("Enter a message to sent to server : ");
	fgets(buf, 100, stdin);
	int k = sendto(sd, buf, 100, 0, (struct sockaddr*) &server, sizeof(server));
	if (k == -1) {
		printf("Error in sendto()");
	}
	return 0;
}