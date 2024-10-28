#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind the socket to a specific address and port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080); // Listen on port 8080

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Start listening for incoming connections
    listen(server_fd, 5);

    printf("Web server listening on port 8080...\n");

    while (1) {
        // Accept incoming connections
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            perror("Error accepting connection");
            continue;
        }

        // Send a simple "Hello, World!" response to the client
        char response[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Hello, World!</h1>";
        send(client_fd, response, sizeof(response), 0);

        // Close the client socket
        close(client_fd);
    }

    // Close the server socket (unreachable in this example)
    close(server_fd);

    return 0;
}