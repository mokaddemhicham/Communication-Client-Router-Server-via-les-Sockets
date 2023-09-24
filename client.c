#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

char *crc(char str[16]){

    char *px = (char*)malloc(sizeof(char)*19);
    for(int i = 0; i < 16; i++){
        px[i] = str[i];
    }
    for(int i = 16; i < 19; i++){
        px[i] = '0';
    }
    
    char gx[4] = "1101";
    
    char t1[4];
    char *tr = (char*)malloc(sizeof(char)*3);

    for(int i = 0; i < 4; i++){
        t1[i] = px[i];
    }
    for(int i = 4; i < 19; i++){
        for(int j = 0; j < 3; j++){
            if(t1[j] == gx[j]){
                tr[j] = '0';
            }else{
                tr[j] = '1';
            }
        }
        if(tr[0] == '1'){
            for(int i = 0; i < 4; i++){
                t1[i] = tr[i];
            }
        }
        t1[0] = tr[1];
        t1[1] = tr[2];
        t1[2] = tr[3];
        t1[3] = tr[i];
		for(int i = 0; i < 4; i++){
			printf("%c", t1[i]);
		}
		printf("\n");
    }
    return tr;
}


void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("votre message : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n');
		crc(buff);
		write(sockfd, buff, sizeof(buff));

		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main()
{
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
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}

