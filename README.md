# JavaSerial
Multiplataform, lightweight and fast library to connect serial with Java


# Pre-Requisites

- Java JDK (javac in your PATH)
- Visual Studio If you are running Windows

# Build

```
cmake .
```

## Examples

Arduino interfacing
```arduino
// Arduino code

bool state = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:

  while(Serial.available() > 0) {
    char read = Serial.read();
    if(read == 't') state = true;
    if(read == 'f') state = false;
  }

  if(state) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  delay(1000);
  Serial.print("Hello world");
}

```

```java
JavaSerialLib lib = new JavaSerialLib("COM8", 9600);
if(lib.connect()) {

    while (true) {

        lib.write('t');
        Thread.sleep(1000);
        lib.write('f');
        Thread.sleep(1000);

        lib.write(data);
        int size = 0;
        byte[] buff = new byte[1024];
        while((size = lib.read(buff)) >= 0) {
            System.out.println(new String(buff, 0, size));
        }
    }

}
```

Also you can use Native C:

```c
// C Code
baseSerial * serial = serial_create("COM8", 9600);
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
```
