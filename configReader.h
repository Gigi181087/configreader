#ifndef _CONFIGREADER_H_
#define _CONFIGREADER_H_

#define CFGREADER_ERROR_ALLOCFAILED     -2
#define CFGREADER_ERROR_FILEOPEN        -3

typedef struct config config_t;

int ReadConfigFile(const char*, config_t**);

char* GetValueByParam(config_t*, const char*);

void SetValueByParam(config_t*, const char*. char*);

#endif // _CONFIGREADER_H_

// todo: comments!!!
