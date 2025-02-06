!OBJREADERTEST_PRI {
CONFIG += OBJREADERTEST_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/../ObjReader.pri)

HEADERS += \
	$$PWD/objreadertest.h \
	
SOURCES += \
	$$PWD/objreadertest.cpp \
}
