//
// Created by Manuel Muñoz on 29/10/17.
//

#include <Serial.h>
#include "Serial.h"
#include "SerialUnix.h"


baseSerial * serial_create(char * portName, long baudRate) {

    baseSerial * serial = _serial_create(portName, baudRate);
    serial->privateSerial = (privateSerial*)malloc(sizeof(privateSerial));
    return serial;

}

cbool serial_connect(baseSerial * serial)
{

    int fd;                             // File descriptor
// Open port
    serial->privateSerial->fd = fd = open(serial->portName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1){
        printf("Device cannot be opened.\n");
        return SERIAL_FALSE;
    }
    struct termios options;

    fcntl(fd, F_SETFL, FNDELAY);                    // Open the device in nonblocking mode

// Set parameters
    tcgetattr(fd, &options);                        // Get the current options of the port
    bzero(&options, sizeof(options));               // Clear all the options
    speed_t         Speed;
    switch (serial->baudRate)                               // Set the speed (baudRate)
    {
        case 110  :     Speed=B110; break;
        case 300  :     Speed=B300; break;
        case 600  :     Speed=B600; break;
        case 1200 :     Speed=B1200; break;
        case 2400 :     Speed=B2400; break;
        case 4800 :     Speed=B4800; break;
        case 9600 :     Speed=B9600; break;
        case 19200 :    Speed=B19200; break;
        case 38400 :    Speed=B38400; break;
        case 57600 :    Speed=B57600; break;
        case 115200 :   Speed=B115200; break;
        default : exit(-4);
    }
    cfsetispeed(&options, Speed);                   // Set the baud rate at 115200 bauds
    cfsetospeed(&options, Speed);
    options.c_cflag |= ( CLOCAL | CREAD |  CS8);    // Configure the device : 8 bits, no parity, no control
    options.c_iflag |= ( IGNPAR | IGNBRK );
    options.c_cc[VTIME]=0;                          // Timer unused
    options.c_cc[VMIN]=0;                           // At least on character before satisfy reading
    tcsetattr(fd, TCSANOW, &options);               // Activate the settings
    usleep(2000);
    return SERIAL_TRUE;
}

int serial_write(baseSerial * serial, char * buffer, int nbChar)
{

    return write(serial->privateSerial->fd, buffer, nbChar);
}

int serial_read(baseSerial * serial, char * buffer, int size) {
    return read(serial->privateSerial->fd, buffer, size);
}

cbool serial_close(baseSerial * serial)
{
    fclose(serial->privateSerial->fd);
}