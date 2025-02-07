!MYMESH_PRI {
CONFIG += MYMESH_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/BoundingBox.pri)

HEADERS += \
	$$PWD/mesh.h
	
SOURCES += \
	$$PWD/mesh.cpp
}
