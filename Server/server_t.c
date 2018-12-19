#include "headers.h"
#include "prototypes.h"


pthread_mutex_t lock;

struct sockaddr_in my_addr;
struct sockaddr_in cl_addr;
socklen_t addr_size;

int main(int argc, char *argv[])
{
	int  port_no;
	int sfd, *socket_fd;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&my_addr, 0, sizeof(struct sockaddr_in));  /* Clear structure */
	
	port_no = atoi(argv[1]);
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(port_no);
	
	if (bind(sfd, (struct sockaddr *) &my_addr,sizeof(struct sockaddr_in)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	else 
		printf("\tbind success\n");

	if (listen(sfd, LISTEN_BACKLOG) == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	else 
		printf("\tlisten success\n");
	pthread_t thread_id;
	socket_fd = malloc(1);
	*socket_fd = sfd;	
	pthread_create(&thread_id, NULL, accept_clients,(void *)socket_fd);
	pthread_join(thread_id,NULL);

}
void *accept_clients(void *arg)
{
	int i=0, *new_socket_fd;
	int sfd, cfd;
	sfd = *(int *)arg;
	static int count=0;
	pthread_attr_t attr;
	int rc;

	rc = pthread_attr_init(&attr);
	printf("attr_init: %d\n",rc);
	rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	printf("attr_setdetachedstate: %d\n",rc);

	addr_size = sizeof(struct sockaddr_in);
	while(1)
	{
		cfd = accept(sfd, (struct sockaddr *) &my_addr,&addr_size);
		if (cfd < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("\t\t\t\tCount = {%d}\n", ++count);
		pthread_t thread_t;	
		new_socket_fd = malloc(1);
		*new_socket_fd = cfd;	
		pthread_create(&thread_t, &attr, requestProcess,(void *)new_socket_fd);//creating detachable thread
		//pthread_join(thread_t,NULL);
	}
}

