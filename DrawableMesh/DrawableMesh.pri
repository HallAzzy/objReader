!DRAWABLEMESH_PRI {
CONFIG += DRAWABLEMESH_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/../DrawableObject/DrawableObject.pri)

HEADERS += \
	$$PWD/drawablemesh.h
	
SOURCES += \
	$$PWD/drawablemesh.cpp
}
