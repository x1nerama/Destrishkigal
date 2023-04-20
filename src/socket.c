#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 15000 // Define a constant for maximum buffer size

int main(int argc, char **argv) {
    char buffer[MAX_BUFFER_SIZE];
    int bufferSize = atoi(argv[3]);
    char payload[MAX_BUFFER_SIZE];
    int loopCounter = 0;
    int bufferLength = 0;

    // Check if buffer size is within the allowed limit
    if (bufferSize > MAX_BUFFER_SIZE) {
        printf("%d", MAX_BUFFER_SIZE);
        return EXIT_FAILURE;
    }

    do {
        if (loopCounter >= 1) {
            bufferSize += 100;
            if (bufferSize > MAX_BUFFER_SIZE) {
                printf("%d", MAX_BUFFER_SIZE);
                break;
            }
        }
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            printf("Error creating socket: %s\n", strerror(errno));
            break;
        }
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(argv[2]));

        if (inet_pton(AF_INET, argv[1], &server.sin_addr) == -1) {
            printf("Error converting IP address: %s\n", strerror(errno));
            break;
        }

        if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
            printf("Error connecting to server: %s\n", strerror(errno));
            break;
        }
        memset(payload, 'A', bufferSize);
        payload[bufferSize - 1] = '\0';
        strcpy(buffer, argv[5]);
        strcat(buffer, payload);
        bufferLength = strlen(buffer);
        if (write(sockfd, buffer, bufferLength) == -1) {
            printf("Error sending data: %s\n", strerror(errno));
            break;
        }
        loopCounter++;
    } while (strcmp(argv[4], "y") == 0);
    printf("%d", bufferLength);
    return EXIT_SUCCESS;
}