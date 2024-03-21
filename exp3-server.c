#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		printf("Error in socket creation");
		return -1;
	}
	struct sockaddr_in client, server;
	server.sin_family = AF_INET;
	server.sin_port = 6969;
	server.sin_addr.s_addr = INADDR_ANY;
	client.sin_family = AF_INET;
	client.sin_port = 6969;
	client.sin_addr.s_addr = INADDR_ANY;
	int k = bind(sd, (struct sockaddr * ) &server, sizeof(server));
	if (k == -1) {
		printf("Error in binding");
		return -1;
	}
	k = listen(sd, 5);
	if (k == -1) {
		printf("Error in listening");
		return -1;
	}
	int len = sizeof(client);
	int tmpSd = accept(sd, (struct sockaddr * ) &client, &len);
	if (tmpSd == -1) {
		printf("Error in temporary socket creation");
		return -1;
	}
	char buf[100];
	k = recv(tmpSd, buf, 100, 0);
	if (k == -1) {
		printf("Error in receiving");
		return -1;
	}
	printf("Message got from client is : %s", buf);
	close(tmpSd);
	close(sd);
	return 0;
}
