#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>   
#include <netdb.h>

int main(int argc, char *argv[])
{
	int sfd, cfd, port_no;
	char buf[20];
	struct sockaddr_in  peer_addr;
	struct hostent *server;

	socklen_t peer_addr_size;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	else
		printf("\t socket success\n");
	port_no = atoi(argv[2]);	

	server = gethostbyname(argv[1]);
	if (server == NULL) 
	{
       		fprintf(stderr, "ERROR, no such host\n");
	        exit(0);
	}   
	peer_addr.sin_family = AF_INET;
	memmove((char *) &peer_addr.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
        peer_addr.sin_port = htons(port_no);

	peer_addr_size = sizeof(struct sockaddr_in);
       
	int ret=0;
	ret = connect(sfd, (struct sockaddr *) &peer_addr, peer_addr_size);
	if (ret == -1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	else
		printf("\t connect success\n");
	
	buf[0] = 25;
	buf[1] = '*';	
	buf[2] = 2;
        ret = write(sfd,&buf,3);

	read(sfd,&buf[3],1);
	close(sfd);	
	printf("\t\t\t  Result is : {%d}  \n",buf[3]);
	//sleep(4);
return 0;
}

