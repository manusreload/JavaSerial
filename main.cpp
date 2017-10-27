#include <jni.h>
#include  <iostream>
#include <Serial.h>


using namespace std;


int main(int argc, char ** argv) {
    cout << "Well done!" << endl;

    baseSerial * serial = serial_create("COM8", 9600);


//    pSerial * serial = newSerialInstance("COM8", 9600);
//    if(serial->Connect(4000)) {
//        char * data = "world is the world!\0";
//        serial->WriteData(data, strlen(data));
//        char * buff = new char[100];
//        int size;
//        while( (size = serial->ReadData(buff, 99 ) )>= 0) {
//            if(size > 0) {
//                buff[size] = '\0';
//                cout << "Read size: " << size << endl;
//                cout << buff << endl;
//            }
//        }
//
//    }
}