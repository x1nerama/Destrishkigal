#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER 4096
#define ERROR_COLOR "\e[4;31m"
#define RESET_COLOR "\e[0;37m"
#define INFORMATION_COLOR "\e[0;36m"
#define SUCCESSFUL_COLOR "\e[0;32m"

struct paramsForSocket {
    const char* ipAddress;
    int port; 
    const char* payload;
    int loopCounter; 
};

/* Important Variables */
const char* ipAddressKey;  
const char* ipStart;  
const char* portKey;  
const char* portStart;  
const char* payloadStart;  
const char* payloadKey;  
const char* lpStart;  
const char* lpKey;  

/* Messages */
char e[] = "[-]";
char s[] = "[+]";
char i[] = "[*]";

char* getValues(const char* valueKey, const char* valueLength, const char* jsonData) {
    const char* valueStart = strstr(jsonData, valueKey);
    if (valueStart == NULL) {
        printf("%s%s Failed to get value!%s\n", ERROR_COLOR, e, RESET_COLOR);
        return NULL;
    }
    valueStart += strlen(valueKey);
    
    const char* valueEnd = strchr(valueStart, '\"');
    if (valueEnd == NULL) {
        printf("%s%s Invalid value!%s\n", ERROR_COLOR, e, RESET_COLOR);
        return NULL;
    }
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
    if (ipAddress == NULL) {
        printf("%s%s Failed to get IP address.%s\n", ERROR_COLOR, e, RESET_COLOR);
        fclose(fp);
        free(buffer);
        return;
    }
    pfss->ipAddress = ipAddress;

    char* port = getValues(portKey, "\",", jsonData);
    if (port == NULL) {
        printf("%s%s Failed to get port.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    pfss->port = atoi(port);

    char* payload = getValues(payloadKey, "\",", jsonData);
    if (payload == NULL) {
        printf("%s%s Failed to get payload.%s\n", ERROR_COLOR, e, RESET_COLOR);
    } 
    pfss->payload = payload;

    char* lCounter = getValues(lpKey, "\",", jsonData);
    if (lCounter == NULL) {
        printf("%s%s Failed to get Loop Counter.%s\n", ERROR_COLOR, e, RESET_COLOR);
    }
    pfss->loopCounter = atoi(lCounter);
    
    fclose(fp);
    free(buffer);
}