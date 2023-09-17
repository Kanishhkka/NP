#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdio.h>
#include<string.h>

int main(){
	char str[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;	
	bzero(str,100); 
	bzero(&servaddr,sizeof(servaddr));
	
	//1-listen
	
	//create a socket:
	listen_fd=socket(AF_INET,SOCK_STREAM,0);
	
	//define the parameters of server:
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr= htonl(INADDR_ANY);
	servaddr.sin_port=htons(21000);
	
	//2-bind server and socket
	bind(listen_fd,(struct sockaddr *)&servaddr, sizeof(servaddr));
	
	//3-listen stage
	listen(listen_fd,5); 
	
	//4-accept stage :
	comm_fd=accept(listen_fd,(struct sockaddr *)NULL,NULL);
	
	//5-to receive the data:
	recv(comm_fd,str,100,0);
	printf("Received Data from client is %s",str);
	
	//6-to sendback whatever is received
	send(comm_fd,str,strlen(str),0);
	
	//close the communication
	close(comm_fd);
	close(listen_fd);
	
}
