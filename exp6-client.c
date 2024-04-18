#include<stdio.h>

#include<string.h>

#include<sys/socket.h>

#include<sys/types.h>

#include<netinet/in.h>

#include<arpa/inet.h>

#include<fcntl.h>

#include<stdlib.h>

int main(int argc, char * argv[])

{



int sock_fd,n;

struct sockaddr_in servaddr; 
char buff[100];

if(argc != 3)

{

fprintf(stderr, "Usage: ./client IPaddress_of_server port\n");

exit(1);
}
if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) <0)
{
printf("Cannot create socket\n");
exit(1);

}


bzero((char*)&servaddr, sizeof(servaddr));

servaddr.sin_family = AF_INET;

servaddr.sin_port = htons(atoi(argv[2]));
inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

n = sendto(sock_fd, "" ,1,0, (struct sockaddr*)&servaddr,sizeof(servaddr));

if(n < 0)
{

perror("error in sending"); 
exit(1);

}
if((n= recvfrom(sock_fd,buff, sizeof(buff), 0, NULL,NULL)) == -1)

{

perror("read error from server:"); 
exit(1);

}
printf("the current time of the system is %s\n",buff);
}
