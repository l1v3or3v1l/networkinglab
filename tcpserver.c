#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		printf("Error in socket creation");
	}
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 6969;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 6969;
	int k = bind(sd, (struct sockaddr*) &server, sizeof(server));
	if (k == -1) {
		printf("Error in binding");
	}
	k = listen(sd, 5);
	if (k == -1) {
		printf("Error in listening");
	}
	int len = sizeof(client);
	int tmpSd = accept(sd, (struct sockaddr*) &client, &len);
	if (tmpSd == -1) {
		printf("Error in temporary socket creation");
	}
	char buf[100];
	k = recv(tmpSd, buf, 100, 0);
	if (k == -1) {
		printf("Error in receiving");
	}
	printf("Message got from client is : %s", buf);
	printf("Enter message : ");
	fgets(buf, 100, stdin);
	k = send(tmpSd, buf, 100, 0);
	if (k == -1) {
		printf("Error in sending");
	}

	close(tmpSd);
	return 0;
}
