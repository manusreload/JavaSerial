//
// Created by MMunoz on 25/10/2017.
//

#include "com_manus_JavaSerialLib.h"
#include "Serial.h"
JNIEXPORT void JNICALL Java_com_manus_JavaSerialLib_sayHello(JNIEnv * a, jobject b)
{
    printf("Hello World! %d\n", b);
    return;

}

JNIEXPORT jobject JNICALL Java_com_manus_JavaSerialLib_init
        (JNIEnv * env, jobject obj, jstring comm, jint baudRate) {
    char * portName;
    portName = (*env)->GetStringUTFChars( env, comm , NULL ) ;
    baseSerial * serial = serial_create(portName, baudRate);
    jobject bb = (*env)->NewDirectByteBuffer(env, (void*) serial, sizeof(baseSerial));
    return bb;
}


JNIEXPORT jboolean JNICALL Java_com_manus_JavaSerialLib_connect
        (JNIEnv * env, jobject obj, jobject lp, jint timeout)
{
    baseSerial* data = (baseSerial*) (*env)->GetDirectBufferAddress(env, lp);
    return serial_connect(data) == SERIAL_TRUE;
}


JNIEXPORT jint JNICALL Java_com_manus_JavaSerialLib_write
        (JNIEnv * env, jobject obj, jobject lp, jbyteArray array, jint size) {
    int len = (*env)->GetArrayLength (env, array);
    char* buf = malloc(len);
    (*env)->GetByteArrayRegion (env, array, 0, len, (buf)); // get data from array
    baseSerial* serial = (baseSerial*) (*env)->GetDirectBufferAddress(env, lp); // recover serial structure
    return serial_write(serial, buf, size);
}
JNIEXPORT jint JNICALL Java_com_manus_JavaSerialLib_read
        (JNIEnv * env, jobject obj, jobject lp, jbyteArray data, jint size)
{
    char * buf = (char *) malloc(size * sizeof(char));
    baseSerial* serial = (baseSerial*) (*env)->GetDirectBufferAddress(env, lp); // recover serial structure
    int read = serial_read(serial, buf, size);
    (*env)->SetByteArrayRegion(env, data, 0, read,(jbyte *) buf);
    return read;
}