#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() 
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *message = "Hello from server";

	// 1. Create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == -1) 
	{
		perror("Socket failed");
		exit(1);
	}

	// 2. Define address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // any IP
	address.sin_port = htons(8080);

	// 3. Bind
	if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("Bind failed");
		exit(1);
	}

	// 4. Listen
	if(listen(server_fd, 3) < 0) {
		perror("Listen failed");
		exit(1);
	}

	printf("Server is waiting...\n");

	// 5. Accept
	new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if(new_socket < 0) {
		perror("Accept failed");
		exit(1);
	}

	// 6. Read from client
	read(new_socket, buffer, 1024);
	printf("Client: %s\n", buffer);

	// 7. Send response
	write(new_socket, message, strlen(message));

	// 8. Close
	close(new_socket);
	close(server_fd);

	return 0;
}
