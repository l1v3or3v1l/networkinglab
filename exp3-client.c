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
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = 6969;
	client.sin_addr.s_addr = INADDR_ANY;
	int k = connect(sd, (struct sockaddr * ) &client, sizeof(client));
	if (k == -1) {
		printf("Error in connecting to server");
		return -1;
	}
	printf("Enter data to be send : ");
	char buf[100];
	fgets(buf, 100, stdin);
	k = send(sd, buf, 100, 0);
	if (k == -1) {
		printf("Error in sending");
		return -1;
	}
	close(sd);
	return 0;
}
