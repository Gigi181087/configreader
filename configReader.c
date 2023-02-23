#include "configReader.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

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

int CfgReader_ReadConfigFile(const char* file, CONFIG** configs) {

    if (*configs == NULL) {

        if (*configs = (CONFIG*)malloc(sizeof(CONFIG)) == NULL) {
            lastError = CFGREADER_ERROR_ALLOCFAILED;

            return (-1);
        }
        (*configs)->length = 0;
    }
    FILE* fp;

    if (fp = fopen(file, 'r') == NULL) {
        lastError = CFGREADER_ERROR_FILEOPEN;

        return (-1);
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

            if ((*configs)->parameter[(*configs)->length].name = (char*)malloc(STRLEN * sizeof(char)) == NULL) {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return (-1);
            }
            memset((*configs)->parameter[(*configs)->length].name, '\0', STRLEN * sizeof(char));

            if ((*configs)->parameter[(*configs)->length].value = (char*)malloc(STRLEN * sizeof(char)) == NULL) {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return (-1);
            }
            memset((*configs)->parameter[(*configs)->length].value, '\0', STRLEN * sizeof(char));
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
                    (*configs)->parameter[(*configs)->length].name[len] = s[len];
                }
            }

            if (realloc((*configs)->parameter[(*configs)->length].name, ++len * sizeof(char)) == NULL) {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return (-1);
            }
            int i = 0;

            for (; s[len] != '\0'; len++, i++) {

                if (s[len] == '\0') {
                    break;
                }
                else {
                    (*configs)->parameter[(*configs)->length].value[i] = s[len];
                }
            }

            if (realloc((*configs)->parameter[(*configs)->length].name, ++i * sizeof(char)) == NULL) {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return (-1);
            }
            ((*configs)->length)++;
        }
    }
}

char* CfgReader_GetValueByParam(CONFIG* configs, const char* param) {

    for (int i = 0; i < configs->length; i++) {

        if (!strcmp(configs->parameter[i].name, param)) {

            return (configs->parameter[i].value);
        }
    }
    return NULL;
}

void CfgReader_SetValueByParam(CONFIG* configs, const char* param, char* value) {

    for (int i = 0; i < configs->length; i++) {

        if (!strcmp(configs->parameter[i].name, param)) {
            int _len = strlen(configs->parameter[i].value) + 1;

            if (realloc(configs->parameter[i].value, _len * sizeof(char)) == NULL)
            {
                lastError = CFGREADER_ERROR_ALLOCFAILED;

                return -1;
            }
            memset(configs->parameter[i].value, '\0', _len);
            strcpy(configs->parameter[i].value, (const char*)value);
        }
    }

    return NULL;
}

int CfgReader_GetLastError() {
    int retVal = lastError;
    lastError = 0;

    return retVal;
}
