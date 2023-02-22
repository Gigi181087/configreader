#ifndef _CONFIGREADER_H_
#define _CONFIGREADER_H_

#define CFGREADER_ERROR_ALLOCFAILED     -2
#define CFGREADER_ERROR_FILEOPEN        -3

typedef struct config config_t;

int CfgReader_ReadConfigFile(const char*, config_t**);

char* CfgReader_GetValueByParam(config_t*, const char*);

void CfgReader_SetValueByParam(config_t*, const char*. char*);

int CfgReader_GedtLastError(void);

#endif // _CONFIGREADER_H_

// todo: comments!!!
