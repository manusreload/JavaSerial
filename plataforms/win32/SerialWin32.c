//
// Created by MMunoz on 26/10/2017.
//
#include <Serial.h>
#include <stdio.h>
#include "SerialWin32.h"
baseSerial * serial_create(char * portName, long baudRate) {

    baseSerial * serial = serial_alloc();
    serial->connected = 0;
    serial->portName = malloc(strlen(portName));
    memcpy(serial->portName, portName, strlen(portName) + 1); // + 1 to include the \0 character
    serial->baudRate = baudRate;

    serial->privateSerial = (privateSerial *) malloc(sizeof(privateSerial));
    serial->privateSerial->errors = (LPDWORD) malloc(sizeof(LPDWORD));
    serial->privateSerial->status = (LPCOMSTAT) malloc(sizeof(LPCOMSTAT));
    return serial;
}

cbool serial_connect(baseSerial * serial)
{
    printf("OK Port: %s\n", serial->portName);
    serial->connected = 0;
    serial->privateSerial->hSerial = CreateFile(serial->portName,
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);


    //Check if the connection was successfull
    if(serial->privateSerial->hSerial==INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if(GetLastError()==ERROR_FILE_NOT_FOUND){

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", serial->portName);

        }
        else
        {
            printf("ERROR!!!");
        }
        return SERIAL_FALSE;
    }
    else
    {
        //If connected we try to set the comm parameters
        DCB dcbSerialParams = {0};

        //Try to get the current
        if (!GetCommState(serial->privateSerial->hSerial, &dcbSerialParams))
        {
            //If impossible, show an error
            printf("failed to get current serial parameters!");
            return SERIAL_FALSE;
        }
        else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate=serial->baudRate;
            dcbSerialParams.ByteSize=8;
            dcbSerialParams.StopBits=ONESTOPBIT;
            dcbSerialParams.Parity=NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

            //Set the parameters and check for their proper application
            if(!SetCommState(serial->privateSerial->hSerial, &dcbSerialParams))
            {
                printf("ALERT: Could not set Serial Port parameters");
            }
            else
            {
                //If everything went fine we're connected
                serial->connected = SERIAL_TRUE;
                //Flush any remaining characters in the buffers
                PurgeComm(serial->privateSerial->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //We wait 2s as the arduino board will be reseting
                Sleep(2000);
                return SERIAL_TRUE;
            }
        }
    }
    return SERIAL_FALSE;
}

int serial_write(baseSerial * serial, char * buffer, int nbChar)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if (!WriteFile(serial->privateSerial->hSerial, (void *)buffer, nbChar, &bytesSend, 0)) {
        //In case it don't work get comm error and return false
        ClearCommError(serial->privateSerial->hSerial, serial->privateSerial->errors, serial->privateSerial->status);
        printf("Error in write: %d\n", *serial->privateSerial->errors);
        return SERIAL_ERROR;
    }
    else {
        return bytesSend;
    }
}


int serial_read(baseSerial * serial, char * buffer, int size) {
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(serial->privateSerial->hSerial, serial->privateSerial->errors, serial->privateSerial->status);

    LPCOMSTAT status = serial->privateSerial->status;
    //Check if there is something to read
    if(status->cbInQue>0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if(status->cbInQue>size)
        {
            toRead = size;
        }
        else
        {
            toRead = status->cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(serial->privateSerial->hSerial, buffer, toRead, &bytesRead, NULL) )
        {
            buffer[bytesRead] = '\0';
            printf("Read(%d): %s\n", bytesRead, buffer);
            return bytesRead;
        } else {
            return SERIAL_ERROR;
        }

    }

    //If nothing has been read, or that an error was detected return 0
    return 0;
}
//
//SerialWin32::SerialWin32(const char *portName, long baudRate) : portName(portName), baudRate(baudRate) {
//    this->connected = static_cast<bool *>(malloc(1));
//    printf("Costruct %s. this p: %016x, connected p: %016x\n", this->portName, this, &this->baudRate);
//}
//SerialWin32::~SerialWin32() {
//    if(this->connected)
//    {
//        //We're no longer connected
//        this->connected = false;
//        //Close the serial handler
//        CloseHandle(this->hSerial);
//    }
//}
//
//int SerialWin32::Connect(const long timeout) {
//    printf("OK1 %016x %016x\n", this, &this->connected);
//    printf("OK2\n");
//    this->hSerial = CreateFile(portName,
//                               GENERIC_READ | GENERIC_WRITE,
//                               0,
//                               NULL,
//                               OPEN_EXISTING,
//                               FILE_ATTRIBUTE_NORMAL,
//                               NULL);
//
//    printf("OK3\n");
//}
//
//int SerialWin32::ReadData(char *buffer, unsigned int nbChar) {
//    //Number of bytes we'll have read
//    DWORD bytesRead;
//    //Number of bytes we'll really ask to read
//    unsigned int toRead;
//
//    //Use the ClearCommError function to get status info on the Serial port
//    ClearCommError(this->hSerial, &this->errors, &this->status);
//
//    //Check if there is something to read
//    if(this->status.cbInQue>0)
//    {
//        //If there is we check if there is enough data to read the required number
//        //of characters, if not we'll read only the available characters to prevent
//        //locking of the application.
//        if(this->status.cbInQue>nbChar)
//        {
//            toRead = nbChar;
//        }
//        else
//        {
//            toRead = this->status.cbInQue;
//        }
//
//        //Try to read the require number of chars, and return the number of read bytes on success
//        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) )
//        {
//            return bytesRead;
//        }
//
//    }
//
//    //If nothing has been read, or that an error was detected return 0
//    return 0;
//}
//
//bool SerialWin32::WriteData(const char *buffer, unsigned int nbChar) {
//    DWORD bytesSend;
//
//    //Try to write the buffer on the Serial port
//    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
//    {
//        //In case it don't work get comm error and return false
//        ClearCommError(this->hSerial, &this->errors, &this->status);
//
//        return false;
//    }
//    else
//        return true;
//}


