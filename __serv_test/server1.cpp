#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

#define PORT 8081
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
	struct addrinfo hints;
	struct addrinfo *real = new struct addrinfo;
    // struct sockaddr_in address;
    // int addrlen = sizeof(address);
    
	// memset(reinterpret_cast<char *>(&hints), 0, sizeof(struct addrinfo));
	memset(reinterpret_cast<char *>(&real), 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	char *hello = "HTTP/0.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons( PORT );
    
    // memset(address.sin_zero, 0, sizeof address.sin_zero);
    
	if (getaddrinfo("127.0.0.1", "8080", &hints, &real));
	{
		perror("aaaa");
		exit(1);
	}
    
    if (bind(server_fd, (struct sockaddr *)real->ai_addr, sizeof(real->ai_addrlen))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)real->ai_addr, (socklen_t*)&real->ai_addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
    return 0;
}