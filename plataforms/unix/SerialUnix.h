//
// Created by Manuel Muñoz on 29/10/17.
//

#ifndef JAVA_SERIAL_SERIALUNIX_H_H
#define JAVA_SERIAL_SERIALUNIX_H_H

#include <stdlib.h>
#include <fcntl.h>
#include <sys/termios.h>
#include <strings.h>
#include <printf.h>
#include <zconf.h>
#include "Serial.h"

typedef struct {
    int fd;
} privateSerial;

#endif //JAVA_SERIAL_SERIALUNIX_H_H
