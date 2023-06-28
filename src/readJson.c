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
char* payloadStart;
char* payloadKey;
char* lpStart;
char* lpKey;

/* Message */
char e[] = "[-]";

char* getValues(const char* valueKey, const char* valueLength, const char* jsonData) {
    const char* valueStart = strstr(jsonData, valueKey);
    valueStart += strlen(valueKey);
    
    const char* valueEnd = strchr(valueStart, '\"');
    size_t valueLen = valueEnd - valueStart;
    char* value = (char*)malloc(valueLen + 1);
    strncpy(value, valueStart, valueLen);
    
    value[valueLen] = '\0';
    return value;
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
    payloadKey = "\"payloadName\": \"";
    lpKey = "\"loopCounter\": \"";
    
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
        int portInt = atoi(port);
        free(port);
    }

    char* payload = getValues(payloadKey, "\",", jsonData);
    if (payload == NULL) {
        NULL;
    } 
    else {
        free(payload);
    }

    char* lCounter = getValues(lpKey, "\",", jsonData);
    if (lCounter == NULL) {
        printf("%s%s Failed to get Loop Counter.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    else {
        int lCounterInt = atoi(lCounter);
        free(lCounter);
    }
    fclose(fp);
    free(buffer);
    return EXIT_SUCCESS;
}