#include "configReader.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define STRLEN 4096

static int lastError;

struct config {
    struct config_int* parameter;
    int length;
};

struct config_int {
    char* name;
    char* value;
};

int CfgReader_ReadConfigFile(const char* file, config_t** configs) {

    if (*configs == NULL) {

        if (*configs = (config_t*)malloc(sizeof(config_t)) == NULL) {
            lastError = CFGREADER_ERROR_ALLOCFAILED;

            return (-1);
        }
        (*configs)->length = 0;
    }
    FILE* fp;

    if (fp = fopen(file, 'r') == NULL) {
        lastError = CFGREADER_ERROR_FILEOPEN;

        return (- 1);
    }

    int counter;
    char s[STRLEN];
    memset(s, '\0', STRLEN * sizeof(char));

    while (fgets(s, STRLEN, fp) != NULL) {

        if (s[0] != ';') {

            if ((*configs)->length % 10 == 0) {

                if (realloc((*configs)->parameter, (*configs)->length + 10) == NULL) {
                    lastError = CFGREADER_ERROR_ALLOCFAILED;

                    return (-1);
                }
            }

            if ((*configs)->parameter[(*configs)->length]->name = (char*)malloc(STRLEN * sizeof(char)) == NULL) {
                lastError = CFG_READER_ALLOC_FAILED;

                return (-1);
            }
            memset((*configs)->parameter[(*configs)->length]->name, '\0', STRLEN * sizeof(char));

            if ((*configs)->parameter[(*configs)->length]->value = (char*)malloc(STRLEN * sizeof(char)) == NULL) {
                lastError = CFG_READER_ALLOC_FAILED;

                return (-1);
            }
            memset((*configs)->parameter[(*configs)->length]->value, '\0', STRLEN * sizeof(char));
            int len = 0;
            
            for (; s[len] != '='; len++) {

                if (s[len] == '\0') {
                    lastError = CFGREADER_ERROR_FORMAT;
                    return -1;
                }
                else if (s[len] == '=') {
                    break;
                }
                else {
                    (*configs)->parameter[(*configs)->length]->name[len] = s[len];
                }
            }

            if (realloc((*configs)->parameter[(*configs)->length]->name, ++len * sizeof(char)) == NULL) {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return (-1);
            }
            int i = 0

            for (; s[len] != '\0'; len++, i++) {

                if (s[len] == '\0') {
                    break;
                }
                else {
                    (*configs)->parameter[(*configs)->length]->value[i] = s[len];
                }
            }

            if (realloc((*configs)->parameter[(*configs)->length]->name, ++i * sizeof(char)) == NULL) {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return (-1);
            }
            ((*configs)->length)++;
        }
    }
}

char* CfgReader_GetValueByParam(config_t* configs, const char* param) {

    for (int i = 0; i < index; i++) {

        if (!strcmp(configs->parameter[i]->name, param)) {

            return (configs->parameter[i]->value);
        }
    }

    return NULL;
}

int CfgReader_SetValueByParam(config_t* configs, const char* param, char* value) {

    for (int i = 0; i < index; i++) {

        if (configs->parameter[i]->name == param) {

            if (realloc(configs->parameter[i]->value, strlen(value) * sizeof(char)) == NULL)
            {

                return -1;
            }
            strcpy(configs->parameter[i]->value, (const char*)value);
        }
    }

    return NULL;
}


int CfgReader_GetLastError() {
    int retVal = lastError;
    lastError = 0;

    return retVal;
}
