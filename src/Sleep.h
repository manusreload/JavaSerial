//
// Created by Manuel Muñoz on 29/10/17.
//

#ifndef JAVA_SERIAL_SLEEP_H
#define JAVA_SERIAL_SLEEP_H

#ifdef __APPLE__
#include <zconf.h>


void Sleep(int millis) {
    usleep(millis);
}


#endif

#endif //JAVA_SERIAL_SLEEP_H
