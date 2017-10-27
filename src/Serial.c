//
// Created by MMunoz on 27/10/2017.
//

#include "Serial.h"


baseSerial * serial_alloc() {
    return (baseSerial*) malloc(sizeof(baseSerial));
}
cbool serial_connected(baseSerial * serial) {
    return serial->connected;
}