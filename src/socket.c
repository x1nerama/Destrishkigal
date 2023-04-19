#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "functions.h"
#define MAX_BUFFER_SIZE 10000

int main(int argc, char **argv) {

    int bufferSize = strtol(argv[3], NULL, 10);
    if (bufferSize > MAX_BUFFER_SIZE) {
        printf("Tampon boyutu %d'dan büyük olamaz.\n", MAX_BUFFER_SIZE);
        return EXIT_FAILURE;
    }

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        printf("Soket oluşturma hatası: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &server.sin_addr) <= 0) {
        printf("Geçersiz IP adresi: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    printf("IP ADDRESS --> %s\n", argv[1]);
    printf("PORT NUMBER --> %s\n", argv[2]);

    
        if (connect(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
            printf("Bağlantı hatası: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    
        char buffer[MAX_BUFFER_SIZE];
        if (argv[4] != NULL) {
            strcpy(buffer, argv[4]);
        }
        generate_buffer(buffer, bufferSize);
        printf("Buffer uzunluğu: %s\n", buffer);
    
        if (write(socketfd, buffer, bufferSize) == -1) {
            printf("Yazma hatası: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
        close(socketfd);

    return EXIT_SUCCESS;
}