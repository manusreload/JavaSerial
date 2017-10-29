//
// Created by MMunoz on 27/10/2017.
//

#include "Serial.h"


baseSerial * serial_alloc() {
    return (baseSerial*) malloc(sizeof(baseSerial));
}

baseSerial * _serial_create(char * portName, long baudRate)
{
    baseSerial * serial = serial_alloc();
    serial->connected = 0;
    serial->portName = malloc(strlen(portName));
    memcpy(serial->portName, portName, strlen(portName) + 1); // + 1 to include the \0 character
    serial->baudRate = baudRate;
    return serial;
}
cbool serial_connected(baseSerial * serial) {
    return serial->connected;
}
