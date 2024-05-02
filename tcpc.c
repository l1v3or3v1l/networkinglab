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
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 6969;
	int k = connect(sd, (struct sockaddr*) &client, sizeof(client));
	if (k == -1) {
		printf("Error in connecting to server");
	}
	char buf[100];
	printf("Enter data to be send : ");
	fgets(buf, 100, stdin);
	k = send(sd, buf, 100, 0);
	if (k == -1) {
		printf("Error in sending");
	}
	close(sd);
	return 0;
}