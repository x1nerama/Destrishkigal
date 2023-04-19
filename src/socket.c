#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "functions.h"
#define MAX_BUFFER_SIZE 10000

int bufferSocket(int bufferSize, char *ip_address, int port, char *buffer) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_address, &server.sin_addr) <= 0) {
        perror("inet_pton");
        return EXIT_FAILURE;
    }
    if (connect(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        return EXIT_FAILURE;
    }

    generate_buffer(buffer, bufferSize);
    if (write(socketfd, buffer, bufferSize) == -1) {
        perror("write");
        return EXIT_FAILURE;
    }
    close(socketfd);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    if (argc <= 5) {
        return EXIT_FAILURE;
    }

    int bufferSize = strtol(argv[3], NULL, 10);

    char buffer[MAX_BUFFER_SIZE];
    if (argv[5] != NULL) {
        strcpy(buffer, argv[5]);
    }

    if (strcmp(argv[4], "y") == 0 || strcmp(argv[4], "Y") == 0) {
        int x = 0;
        while (1) {
            x++;
            if (bufferSocket(bufferSize, argv[1], atoi(argv[2]), buffer) == -1) {
                return EXIT_FAILURE;
            }
                if (x == 10) {
                    break;
                }
		bufferSize += 100;
	}
    }
    else {
        if (bufferSocket(bufferSize, argv[1], atoi(argv[2]), buffer) == -1) {
            return EXIT_FAILURE;
        }
    }
    printf("%d\n", strlen(buffer));
    return EXIT_SUCCESS;
}