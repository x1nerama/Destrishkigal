#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 4096

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("text.json", "r");
    if (fp == NULL) {
        printf("Dosya açma hatası.\n");
        return 1;
    }

    // Dosya boyutunu bulma
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    /* dfdfd */
    // Bellek için alan ayırma ve dosya içeriğini okuma
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Bellek tahsisi hatası.\n");
        fclose(fp);
        return 1;
    }
    size_t read_size = fread(buffer, 1, file_size, fp);
    buffer[file_size] = '\0';
    const char* json_data = buffer;

    const char* ipAddressKey = "\"ipAddress\": \"";
    const char* portKey = "\"port\": \"";

    const char* ipAddressStart = strstr(json_data, ipAddressKey);
    const char* portStart = strstr(json_data, portKey);

    if (ipAddressStart == NULL) {
        printf("ipAddress değeri bulunamadı.\n");
    } else {
        ipAddressStart += strlen(ipAddressKey);
        const char* ipAddressEnd = strchr(ipAddressStart, '\"');
        if (ipAddressEnd == NULL) {
            printf("ipAddress değeri bulunamadı.\n");
        } else {
            size_t ipAddressLength = ipAddressEnd - ipAddressStart;
            char* ipAddress = (char*)malloc(ipAddressLength + 1);
            strncpy(ipAddress, ipAddressStart, ipAddressLength);
            ipAddress[ipAddressLength] = '\0';
            printf("%s\n", ipAddress);
            free(ipAddress);
        }
    }

    if (portStart == NULL) {
        printf("port değeri bulunamadı.\n");
    } else {
        portStart += strlen(portKey);
        const char* portEnd = strchr(portStart, '\"');
        if (portEnd == NULL) {
            printf("port değeri bulunamadı.\n");
        } else {
            size_t portLength = portEnd - portStart;
            char* port = (char*)malloc(portLength + 1);
            strncpy(port, portStart, portLength);
            port[portLength] = '\0';
            printf(" %s\n", port);
            free(port);
        }
    }

    fclose(fp);
    free(buffer);
    return 0;
}