!OBJREADER_PRI {
CONFIG += OBJREADER_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)


HEADERS += \
	$$PWD/objreader.h
	
SOURCES += \
	$$PWD/objreader.cpp
}
