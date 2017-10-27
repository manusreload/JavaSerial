//
// Created by MMunoz on 27/10/2017.
//

#ifndef JAVA_SERIAL_SERIALWIN32_H
#define JAVA_SERIAL_SERIALWIN32_H

#include <mem.h>
#include <stdlib.h>
#include <windows.h>
#include "Serial.h"

typedef struct {
    HANDLE hSerial;
    LPDWORD errors;
    LPCOMSTAT status;
} privateSerial;
#endif //JAVA_SERIAL_SERIALWIN32_H
