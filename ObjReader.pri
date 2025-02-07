!OBJREADER_PRI {
CONFIG += OBJREADER_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

icnlude($$PWD/MyMesh.pri)

HEADERS += \
	$$PWD/objreader.h
	
SOURCES += \
	$$PWD/objreader.cpp
}
