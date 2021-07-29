#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define PORTNUM 3389

struct SendPacket{
	uint32_t type;
	char lba[10];
	char data[1000];
	uint32_t offset;
};

int main(void) {
	struct sockaddr_in sin, cli;
	struct hostent *host_entry;
	int sd, ns; 
	
	socklen_t clientlen = sizeof(cli);
	struct SendPacket sPacket;
	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}   

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr(INADDR_ANY);
	
	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("bind");
		exit(1);
	}   
	
	if (listen(sd, 5)) {
		perror("listen");
		exit(1);
	}   
	
	if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen))==-1){
		perror("accept");
		exit(1);
	}   
  
	int GetSize = recv(ns,(struct SendPacket*)&sPacket,sizeof(sPacket),0);
	printf("%s \n",sPacket.data);
	return 0;
}
