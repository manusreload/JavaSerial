package com.manus;


import java.nio.ByteBuffer;

class JavaSerialLib {
    static {
        System.loadLibrary("libjava_serial");
    }
    private native void sayHello();

    private native ByteBuffer init(String portName, int baudRate);
    private native boolean connect(ByteBuffer lp, int timeout);
    private native int write(ByteBuffer lp, byte[] data, int size);
    private native int read(ByteBuffer lp, byte[] data, int count);


    private ByteBuffer struct;
    private int baudRate;
    private String portName;

    public JavaSerialLib(String portName, int baudRate) {
        this.baudRate = baudRate;
        this.portName = portName;
        this.struct = init(portName, baudRate);
    }

    public boolean connect() {
        return connect(struct, 2000);
    }

    public int write(char data) {
        return write((byte) data);
    }
    public int write(byte data) {
        return write(struct, new byte[] {data}, 1);
    }
    public int write(byte[] data) {
        return write(struct, data, data.length);
    }
    public int write(byte[] data, int leng) {
        return write(struct, data, leng);
    }

    public int read(byte[] buff) {
        return read(struct, buff, buff.length);
    }

    public static void main(String[] args)
    {
        System.out.println("Loading...");

        byte data[] = "Hello world!".getBytes();
        try {
            JavaSerialLib lib = new JavaSerialLib("COM8", 9600);
            lib.sayHello();
            if(lib.connect()) {

                while (true) {

                    lib.write('t');
                    Thread.sleep(1000);
                    lib.write('f');
                    Thread.sleep(1000);

                    lib.write(data);
                    int size = 0;
                    byte[] buff = new byte[1024];
                    while((size = lib.read(buff)) > 0) {
                        System.out.println(new String(buff, 0, size));
                    }
                }

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}