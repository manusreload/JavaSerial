cmake_minimum_required(VERSION 3.8)
project(java_serial)

set(CMAKE_CXX_STANDARD 11)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)
if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(${JNI_INCLUDE_DIRS})
include_directories("src")
FILE(GLOB JAVA_SOURCE
        "${CMAKE_CURRENT_SOURCE_DIR}/java/**.java"
        )
set(SOURCE_FILES main.cpp java/com_manus_JavaSerialLib.c src/Serial.c)
if (WIN32)
    #do something
    set(WIN32 TRUE)
    set(SOURCE_FILES ${SOURCE_FILES} plataforms/win32/SerialWin32.c)
endif (WIN32)
add_jar(libserial
        SOURCES java/com/manus/JavaSerialLib.java
        ENTRY_POINT com/manus/JavaSerialLib
        MANIFEST java/Manifest.mf)
add_library(java_serial SHARED ${SOURCE_FILES})

add_executable(java_serial_test ${SOURCE_FILES})