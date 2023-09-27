#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "crc.h"
#define MAX 65
#define PORT 3000
#define SA struct sockaddr

void func(int sockfd,char *buff)
{	
		printf("Trame du client :  %s\n",buff);
		write(sockfd, buff, MAX); //envoie du msg au serveur
}


int main()
{	

	/* Message envoye : 1110010100011000111101110000 */
	
	//longuer de la trame c'est 64 + \0 = 65
	char trame[65] = "0000000000000000000000001110010100011000111101110000000000000000";
	calculerCRC(trame);
	
	
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the router failed...\n");
		exit(0);
	}
	else
		printf("connected to the router..\n");

	// function for chat
	func(sockfd,trame);

	// close the socket
	close(sockfd);
}

