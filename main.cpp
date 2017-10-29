#include <jni.h>
#include  <iostream>
#include <stdlib.h>
#include <Serial.h>
#include <Sleep.h>



using namespace std;


int main(int argc, char ** argv) {
    baseSerial * serial = serial_create("/dev/cu.wchusbserial14210", 9600);
    if(serial_connect(serial)) {
        char * data = "world is the world!\0";
        serial_write(serial, data, strlen(data));
        data = "f\0"; // turn off led
        serial_write(serial, data, strlen(data));
        Sleep(1000);
        data = "t\0"; // turn on led
        serial_write(serial, data, strlen(data));
        Sleep(1000);
        char * buff = new char[100];
        int size;
        while( (size = serial_read(serial, buff, 99 ) ) >= 0) {
            if(size > 0) {
                buff[size] = '\0';
                cout << "Read size: " << size << endl;
                cout << buff << endl;
            }
        }
    }
}