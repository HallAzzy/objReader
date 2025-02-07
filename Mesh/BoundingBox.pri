!BOUNDINGBOX_PRI {
CONFIG += BOUNDINGBOX_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

HEADERS += \
	$$PWD/boundingbox.h
	
SOURCES += \
	$$PWD/boundingbox.cpp
}
