QT += gui
QT += testlib

CONFIG += c++17
CONFIG -= app_bundle

include($$PWD/Mesh/MeshUnitTest/MeshUnitTest.pri)
include($$PWD/ObjReader/ObjReaderUnitTest/ObjReaderTest.pri)


SOURCES += \
        main.cpp

HEADERS +=
