!DRAWABLEMESH_PRI {
CONFIG += DRAWABLEMESH_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/../DrawableObject/DrawableObject.pri)
include($$PWD/FragmentShader.frag)
include($$PWD/VertexShader.vert)

HEADERS += \
	$$PWD/drawablemesh.h
	
SOURCES += \
	$$PWD/drawablemesh.cpp
}
