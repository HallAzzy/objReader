!MYMESH_PRI {
CONFIG += MYMESH_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

HEADERS += \
	$$PWD/mesh.h
	
SOURCES += \
	$$PWD/mesh.cpp
}
