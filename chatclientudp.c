#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
int main()
{
	int sock,len;
	char str1[100],str2[100];
	char flag[100]="exit\n";
	struct sockaddr_in serv;
	bzero(str1,100);
	bzero(str2,100);
	bzero(&serv,sizeof(serv));
	sock=socket(AF_INET,SOCK_DGRAM,0);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=inet_addr("127.0.0.1");
	len=sizeof(serv);
	
	while(1)
	{
	bzero(str1,100);
	bzero(str2,100);
	printf("Send to server:");
	fgets(str1,100,stdin);
	sendto(sock,str1,strlen(str1),0,(struct sockaddr *)&serv, len);
	
	recvfrom(sock,str2,100,0,(struct sockaddr *)&serv,&len);
	printf("Received data is: %s",str2);
	if(strncmp(str2,flag,4)==0)
	{
		printf("Client shutting down...\n");
		break;
	}
	//    else if(strncmp(str1,flag,4)==0){
   //     	printf("Break from client");
   //     	break;
   //     }
        
	}
	close(sock);
	return 0;
}
