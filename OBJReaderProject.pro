QT += gui
QT += testlib

CONFIG += c++17
CONFIG -= app_bundle

include($$PWD/MyMesh.pri)
include($$PWD/unitTests/ObjReaderTest.pri)


SOURCES += \
        main.cpp \
        meshtest.cpp

HEADERS += \
    meshtest.h

