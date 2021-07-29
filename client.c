#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PORTNUM 3389
struct SendPacket{
	uint32_t type;
	char lba[10];
	char data[1000];
	uint32_t offset;
};
int main(void){
	int sd; 
	struct sockaddr_in sin;
	struct SendPacket sPacket;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}   
	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		exit(1);
	}   

	sprintf(sPacket.data,"%s","hello");
	
	if (send(sd,(struct SendPacket*)&sPacket,sizeof(sPacket),0)  == -1) {
		perror("send");
		exit(1);
	}   

//close(sd);
	return 0;
}
