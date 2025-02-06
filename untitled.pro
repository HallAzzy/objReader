QT += gui
QT += testlib

CONFIG += c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/MyMesh.pri)
include($$PWD/ObjReaderTest.pri)

SOURCES += \
        main.cpp \
        meshtest.cpp \
#        mesh.cpp \
#        objreader.cpp \
#        objreadertest.cpp

HEADERS += \
    meshtest.h \
#    mesh.h \
#    objreader.h \
#    objreadertest.h

