QT += gui
QT += testlib
QT += opengl

CONFIG += c++17
CONFIG -= app_bundle

#include($$PWD/Mesh/BoundingBox.pri)
include($$PWD/Mesh/MeshUnitTest/MeshUnitTest.pri)
include($$PWD/ObjReader/ObjReaderUnitTest/ObjReaderTest.pri)
include($$PWD/VertexShader.vert)
include($$PWD/FragmentShader.frag)
include($$PWD/Viewport/Viewport.pri)
include($$PWD/DrawableMesh/DrawableMesh.pri)
include($$PWD/Grid/Grid.pri)


SOURCES += main.cpp \

HEADERS +=

