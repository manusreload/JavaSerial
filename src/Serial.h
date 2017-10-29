//
// Created by MMunoz on 26/10/2017.
//

#ifndef JAVA_SERIAL_SERIAL_H
#define JAVA_SERIAL_SERIAL_H
#define SERIAL_TRUE 1
#define SERIAL_FALSE 0
#define SERIAL_ERROR -1
#include "../plataforms/plataforms.h"
#ifdef  __cplusplus
extern "C" {
#endif

typedef struct {
    char * portName;
    long baudRate;
    int connected;

    privateSerial * privateSerial;
} baseSerial;


typedef int cbool;

baseSerial * serial_alloc();
baseSerial * serial_create(char * portName, long baudRate);
baseSerial * _serial_create(char * portName, long baudRate);

cbool serial_connect(baseSerial * serial);
int serial_write(baseSerial * serial, char * data, int size);
int serial_read(baseSerial * serial, char * buffer, int size);
cbool serial_connected(baseSerial * serial);
cbool serial_close(baseSerial * serial);
#ifdef  __cplusplus
};
#endif


#endif //JAVA_SERIAL_SERIAL_H
