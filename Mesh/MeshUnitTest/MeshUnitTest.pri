!MYMESHUNITTEST_PRI {
CONFIG += MYMESHUNITTEST_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/../MyMesh.pri)

HEADERS += \
	$$PWD/meshtest.h
	
SOURCES += \
	$$PWD/meshtest.cpp
}

