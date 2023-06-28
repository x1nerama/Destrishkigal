#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define BUFFER 4096
#define ERROR_COLOR "\e[4;31m"
#define RESET_COLOR "\e[0;37m"

/* Important Variables */
char* ipAddressKey;
char* ipStart; 
char* portKey;
char* portStart;

/* Message */
char e[] = "[-]";

char* getValues(const char* valueKey, const char* valueLength, const char* jsonData) {
    const char* valueStart = strstr(jsonData, valueKey);
    if (valueStart == NULL) {
        printf("%s%s Value not found.\n", ERROR_COLOR, e);
        return NULL;
    } 
    else {
        valueStart += strlen(valueKey);
        const char* valueEnd = strchr(valueStart, '\"');
        if (valueEnd == NULL) {
            printf("%s%s Value not found.%s\n", ERROR_COLOR, e, RESET_COLOR);
            return EXIT_FAILURE;
        } 
        else {
            size_t valueLen = valueEnd - valueStart;
            if (strlen(valueLength) > valueLen) {
                printf("%s%s Invalid value length.%s\n", ERROR_COLOR, e, RESET_COLOR);
                return EXIT_FAILURE;
            }
            char* value = (char*)malloc(valueLen + 1);
            strncpy(value, valueStart, valueLen);
            value[valueLen] = '\0';
            return value;
        }
    }
}

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("text.json", "r");
    if (fp == NULL) {
        printf("%s%s Failed to open JSON file!%s\n", ERROR_COLOR, e, RESET_COLOR);
        return EXIT_FAILURE;
    }
    
    fseek(fp, 0 , SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("%s%s Failed to allocate memory!%s\n", ERROR_COLOR, e, RESET_COLOR);
        fclose(fp);
        return EXIT_FAILURE;
    }
    
    size_t rSize = fread(buffer, 1, fileSize, fp);
    buffer[fileSize] = '\0';
    const char* jsonData = buffer;
    
    ipAddressKey = "\"ipAddress\": \"";
    portKey = "\"port\": \"";
    
    char* ipAddress = getValues(ipAddressKey, "\",", jsonData);
    if (ipAddress == NULL) {
        printf("%s%s Failed to get ipAddress.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    else {
        
        free(ipAddress);
    }
    
    char* port = getValues(portKey, "\",", jsonData);
    if (port == NULL) {
        printf("%s%s Failed to get port.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    else {

        free(port);
    }
    fclose(fp);
    free(buffer);
    return EXIT_SUCCESS;
}