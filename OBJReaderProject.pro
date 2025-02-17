QT += gui
QT += testlib
QT += opengl

CONFIG += c++17
CONFIG -= app_bundle

#include($$PWD/Mesh/BoundingBox.pri)
include($$PWD/Mesh/MeshUnitTest/MeshUnitTest.pri)
include($$PWD/ObjReader/ObjReaderUnitTest/ObjReaderTest.pri))
include($$PWD/Viewport/Viewport.pri)
include($$PWD/DrawableMesh/DrawableMesh.pri)
include($$PWD/Grid/Grid.pri)
include($$PWD/Camera/Camera.pri)


SOURCES += main.cpp \

HEADERS +=

