#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "readJson.h"
#include "functions.h"

int main() {
    struct paramsForSocket pfs;
    readJson(&pfs);
    const char* targetIp = pfs.ipAddress;
    const char* payload = pfs.payload;
    int targetPort = pfs.port;
    int loopCounter = pfs.loopCounter;
    int size = 10;
    struct sockaddr_in sock;
    sock.sin_addr.s_addr = inet_addr(targetIp);
    sock.sin_family = AF_INET;
    sock.sin_port = htons(targetPort);

    int scket = socket(AF_INET, SOCK_STREAM, 0);
    if (scket == -1) {
        printf("%s%s Failed to Created Socket! Error Code : %d%s\n", ERROR_COLOR, e, errno, RESET_COLOR);
        return EXIT_FAILURE;
    }
    printf("%s%s Created Socket!%s\n", SUCCESSFUL_COLOR, s, RESET_COLOR);

    int cnt = connect(scket, (struct sockaddr *)&sock, sizeof(sock));
    if (cnt == -1) {
        printf("%s%s Failed to Connection to Server! Error Code : %d%s\n", ERROR_COLOR, e, errno, RESET_COLOR);
        return EXIT_FAILURE;
    }
    printf("%s%s Connection Server!%s\n", SUCCESSFUL_COLOR, s, RESET_COLOR);
    char* bufferMalloc = (char*)malloc(strlen(payload) + 1);
    strcpy(bufferMalloc, payload);
    
    while (loopCounter != 0) {
        size_t bufferSize = strlen(bufferMalloc);
        generate_buffer(bufferMalloc, size);

        printf("%s\n", bufferMalloc);
        size += 1;
        loopCounter--;
        sleep(1);
    }
    free(bufferMalloc);
    return EXIT_SUCCESS;
}
