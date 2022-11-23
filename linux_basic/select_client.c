#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netdb.h>
#include <stdlib.h>

#define TCP_PORT 4900

int main(int argc, char** argv)
{
	int ssock;
	struct sockaddr_in connect_addr;
	char mesg[BUFSIZ];
	fd_set readfd;
    int connect_fd;
	int msgsize;

	if(argc < 2)
	{
		printf("Usage : %s IP_ADDRESS\n", argv[0]);
		return -1;
	}
	

	/*if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		return -1;
	}*/

	connect_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(connect_fd == -1){
		perror("socket Connecting Error\n");
		return -1;
	}
	
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_port = htons(atoi(argv[2]));
	connect_addr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(&(connect_addr.sin_zero), 0, 8);



	fgets(mesg, BUFSIZ, stdin);

	/*memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	inet_pton(AF_INET, argv[1], &(servaddr.sin_addr.s_addr));
	servaddr.sin_port = htons(TCP_PORT);*/
	if(connect(connect_fd, (struct sockaddr*)&connect_addr, sizeof(connect_addr)) == -1){
		perror("connecting Error\n");
		return -1;
	}

	FD_ZERO(&readfd);
	while(1){
		FD_SET(0, &readfd);
		FD_SET(connect_fd, &readfd);

		select(connect_fd + 1, &readfd, NULL, NULL, NULL);


		shutdown(ssock, SHUT_WR);			//쓰기 소켓을 닫음
		if(FD_ISSET(connect_fd, &readfd)){
			msgsize = read(connect_fd, mesg, sizeof(mesg));
			if(msgsize <= 0) continue;
			printf("Server Message>>%s", mesg);
		}

		if(FD_ISSET(0, &readfd)){
			memset(mesg, '\0', sizeof(mesg));
			fgets(mesg, 1024, stdin);
			msgsize = strlen(mesg);
			write(connect_fd, mesg, msgsize);
		}
		

		shutdown(ssock, SHUT_RD);
		close(ssock);
	}
	/*if(connect(ssock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect()");
		return -1;
	}*/
	/*if(connect_fd == 0){
		perror("connect()");
		return -1;
	}

	fgets(mesg, BUFSIZ, stdin);*/
	/*if(send(ssock, mesg, BUFSIZ, MSG_DONTWAIT) <= 0)
	{
		perror("send()");
		return -1;
	}*/

	/*if(connect_fd == 1){
		perror("send()");
		return -1;
	}
	
	shutdown(ssock, SHUT_WR);			//쓰기 소켓을 닫음
	
	memset(mesg, 0, BUFSIZ);*/
	/*if(recv(ssock, mesg, BUFSIZ, 0) <= 0)
	{										//데이터를 소켓으로부터 읽음
		perror("recv()");
		return -1;
	}*/
	/*if(connect_fd == 2)
	{
		perror("recv()");
		return -1;
	}

	
	shutdown(ssock, SHUT_RD);
	close(ssock);*/
	return 0;
}
		
