#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 6969;
	server.sin_family = AF_INET;
	sendto(sd, "", 1, 0, (struct sockaddr * ) &server, sizeof(server));
	char buf[100];
	recvfrom(sd, buf, 100, 0, NULL, NULL);
	printf("the current time of system is %s\n", buf);
}
