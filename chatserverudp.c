#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{

//udp protocol
	int sock,c;
	char str[100];
	char flag[100]="exit\n";
	struct sockaddr_in serv,cli;   //to store server address and client info
	bzero(str,100);
	bzero(&serv,sizeof(serv));
	c=sizeof(cli);
	sock=socket(AF_INET,SOCK_DGRAM,0);
	
	//server parameters
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=INADDR_ANY;
	bind(sock,(struct sockaddr *)&serv,sizeof(serv)); //bind operation
	
	while(1)
	{
	bzero(str,100);
	recvfrom(sock,str,100,0,(struct sockaddr *)&cli,&c);  //data receive from client
	printf("Received data is:%s", str);  //print the received data
	bzero(str,100);
	fgets(str,100,stdin);
	
	sendto(sock,str,strlen(str),0,(struct sockaddr *)&cli ,c);  //send data back to client to same address as receiver
	
	if(strncmp(str,flag,4)==0)
	{
		printf("Server shutting down...\n");
		break;
	}
	
	//char * clientaddr=inet_ntoa(cli.sin_addr);
	//printf("Address of client is %s",clientaddr);

	}
	close(sock);
	close(c);
	
}


