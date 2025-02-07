QT += gui
QT += testlib

CONFIG += c++17
CONFIG -= app_bundle

include($$PWD/BoundingBox.pri)
include($$PWD/ObjReader/ObjReaderUnitTest/ObjReaderTest.pri)


SOURCES += \
        main.cpp

HEADERS +=
