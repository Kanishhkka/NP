#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include<arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sock;
    char sendline[100];
    char recvline[100];
    char flag[100]="exit";
    
    struct sockaddr_in servaddr;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(sendline, 100);
    bzero(recvline, 100);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1) {

        bzero(sendline,100);
        bzero(recvline,100);
        printf("Send to server:");
        fgets(sendline, 100, stdin);
        send(sock, sendline, strlen(sendline), 0);
        recv(sock, recvline, 100, 0);
        printf("Server says: %s", recvline);
        
        if(strncmp(recvline,flag,4)==0){
        	printf("Break from server");
        	break;
        }
   //    else if(strncmp(sendline,flag,4)==0){
   //     	printf("Break from client");
   //     	break;
   //     }
        
    }

    close(sock);

    return 0;
}

