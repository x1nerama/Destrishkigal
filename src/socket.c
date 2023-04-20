#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
   char buffer[10000];
   int x = 0;
   int bufferSize = 0;
   do {
    if (x >= 1) {
      bufferSize += 1000;
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

    char payload[bufferSize];
    memset(payload, 'A', bufferSize);  // Payload'ı A harfi ile doldur
    payload[bufferSize-1] = '\0';        // Son karakteri null byte ile bitir

    strcpy(buffer, argv[5]);
    strcat(buffer, payload);

        if (write(sockfd, buffer, strlen(buffer)) == -1) {  // Buffer'ı server'a gönder
            break; 
        }
        x++;
   } while (strcmp(argv[4], "y") == 0); 
  printf("%d\n", strlen(buffer));
  return EXIT_SUCCESS;  
}