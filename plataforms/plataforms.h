//
// Created by MMunoz on 27/10/2017.
//

#ifndef JAVA_SERIAL_PLATAFORMS_H
#define JAVA_SERIAL_PLATAFORMS_H

#ifdef WIN32
#include "../plataforms/win32/SerialWin32.h"
#endif

#if defined(__APPLE__) || defined(__linux__)
#include "../plataforms/unix/SerialUnix.h"
#endif
#endif //JAVA_SERIAL_PLATAFORMS_H
