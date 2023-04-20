#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
    char buffer[15000];
    int bufferSize = atoi(argv[3]);
    char payload[15000];
    int loopCounter = 0;
    int bufferLength = 0; // added variable to keep track of buffer length
    do {
        if (loopCounter >= 1) {
            bufferSize += 100;
            if (bufferLength >= 15000) {
                break;
            }
        }
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
           break;
           printf("%d\n", bufferLength);
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
        memset(payload, 'A', bufferSize);
        payload[bufferSize - 1] = '\0';
        strcpy(buffer, argv[5]);
        strcat(buffer, payload);
        bufferLength = strlen(buffer); // update buffer length
        if (write(sockfd, buffer, bufferLength) == -1) {
            break;
        }
        loopCounter++;
    } while (strcmp(argv[4], "y") == 0);
    printf("%d\n", bufferLength); // print buffer length
    return EXIT_SUCCESS;
}