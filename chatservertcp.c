#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>

int main() {
//tcp
    char str[100];
    char flag[100]="exit";
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    bzero(str, 100);
    bzero(&servaddr, sizeof(servaddr));

    // Create a socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Define the parameters of the server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    // Bind server and socket
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Listen stage
    listen(listen_fd, 10);

 
        comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);

        while (1) {
       	    bzero(str,100);
            recv(comm_fd, str, 100, 0);
            printf("Received data from client is:%s",str);
            bzero(str,100);
            fgets(str,100,stdin);

            // Send back the received data
            send(comm_fd, str, strlen(str), 0);
            if(strncmp(str,flag,4)==0)
            break;
        }

        // Close the communication with this client
        close(comm_fd);

    // Close the server socket
    close(listen_fd);

    return 0;
}



