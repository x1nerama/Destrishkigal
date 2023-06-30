#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define BUFFER 4096
#define ERROR_COLOR "\e[4;31m"
#define RESET_COLOR "\e[0;37m"

struct paramsForSocket {
    const char* ipAddress;
    const char* port; 
    const char* payload;
    const char* loopCounter; 
};

/* Important Variables */
char* ipAddressKey;
char* ipStart; 
char* portKey;
char* portStart;
char* payloadStart;
char* payloadKey;
char* lpStart;
char* lpKey;

/* Error Message */
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

void readJson(struct paramsForSocket* pfss) {
    FILE* fp = fopen("data.json", "r");
    if (fp == NULL) {
        printf("%s%s Failed to open JSON file!%s\n", ERROR_COLOR, e, RESET_COLOR);
        return;
    }
    
    fseek(fp, 0 , SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("%s%s Failed to allocate memory!%s\n", ERROR_COLOR, e, RESET_COLOR);
        fclose(fp);
        return;
    }
    
    size_t rSize = fread(buffer, 1, fileSize, fp);
    buffer[fileSize] = '\0';
    const char* jsonData = buffer;
    
    ipAddressKey = "\"ipAddress\": \"";
    portKey = "\"port\": \"";
    payloadKey = "\"payloadName\": \"";
    lpKey = "\"loopCounter\": \"";
    
    char* ipAddress = getValues(ipAddressKey, "\",", jsonData);
    pfss->ipAddress = ipAddress;
    
    char* port = getValues(portKey, "\",", jsonData);
    if (port == NULL) {
        printf("%s%s Failed to get port.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    pfss->port = port;

    char* payload = getValues(payloadKey, "\",", jsonData);
    if (payload == NULL) {
        printf("%s%s Failed to get payload.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    pfss->payload = payload;

    char* lCounter = getValues(lpKey, "\",", jsonData);
    if (lCounter == NULL) {
        printf("%s%s Failed to get Loop Counter.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    pfss->loopCounter = lCounter;
    
    fclose(fp);
    free(buffer);
}