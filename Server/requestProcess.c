#include "headers.h"
#include "prototypes.h"


void *requestProcess(void *arg)
{
        int ret=0;
        char buf[20];
        int socket_fd = *(int*)arg;
        //pthread_mutex_lock(&lock);
        while(1)
	{
		//        printf("\t\t Server Read on block\n");
       		 memset(buf,0,sizeof(buf));
		ret = read(socket_fd,&buf,10) ;
		if(ret <= 0)
		{
			close(socket_fd);
//	       		 printf("\t\t closing connection !");
        		free(arg);
			pthread_exit(NULL);
			break;
		}
	
		else if(buf[1])
		{       
  //   			 printf("\t\t\t Read: %d %c %d\n",buf[0],buf[1], buf[2]);
			 switch(buf[1]) 
        		{
                	case '+':
                        	buf[3] = addition(buf[0],buf[2]);
                       		 break; 
                	case '-':
                        	buf[3] = subtract(buf[0],buf[2]);
                        	break; 
                	case '*':
                        	buf[3] = multiply(buf[0],buf[2]);
                        	break; 
                	default: 
                        	printf("\t\t !! Wrong request\n");
                        	break;
        		}               

        		ret = write(socket_fd,&buf[3],1);
				//if(ret){printf(" \n  %d  = %dsuccess written to client\n", ret, buf[3]);}
		}
	}

        //pthread_mutex_unlock(&lock);
}
int addition(int x, int y)
{
        int result=0;
        result = x + y;
return result; 
}
int multiply(int x, int y)
{
        int result = 0;
        result = x * y;
return result; 
}
int subtract(int x, int y)
{
        int result=0;
        result =  x - y;
return result; 
}
  
