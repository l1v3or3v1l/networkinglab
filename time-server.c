#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>

int main() {
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 6969;
	bind(sd, (struct sockaddr *) &server, sizeof(server));
	char buf[100];
	int len = sizeof(client);
	time_t curtime;
	while(1) {
		recvfrom(sd, buf, 100, 0, (struct sockaddr *) &client, &len);
		int childpid = fork();
		if (childpid == 0) {
			time(&curtime);
			sprintf(buf, "= %s", ctime(&curtime));
			sendto(sd, buf, 100, 0, (struct sockaddr *) &client, len);
		}
	}
}
