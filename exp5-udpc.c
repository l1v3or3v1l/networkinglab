// udp client driver program 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 

#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	int sockfd, n; 
	struct sockaddr_in servaddr; 
	
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 
	
	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port 
	
	char buffer[100];
	printf("Enter message : ");
	fgets(buffer, 100, stdin);	
	
	sendto(sockfd, buffer, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
	
	// waiting for response 

	// close the descriptor 
	close(sockfd); 
} 

