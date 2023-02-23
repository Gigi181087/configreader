#ifndef _CONFIGREADER_H_
#define _CONFIGREADER_H_


// Errorcodes
#define CFGREADER_ERROR_ALLOCFAILED     -2
#define CFGREADER_ERROR_FILEOPEN        -3
#define CFGREADER_ERROR_FORMAT          -4

typedef struct config CONFIG;

int CfgReader_ReadConfigFile(const char*, CONFIG**);

char* CfgReader_GetValueByParam(CONFIG*, const char*);

void CfgReader_SetValueByParam(CONFIG*, const char*, char*);

int CfgReader_GetLastError(void);

#endif // _CONFIGREADER_H_

// todo: comments!!!
