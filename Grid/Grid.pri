!GRID_PRI {
CONFIG += GRID_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

include($$PWD/../DrawableObject/DrawableObject.pri)

HEADERS += \
	$$PWD/grid.h
	
SOURCES += \
	$$PWD/grid.cpp
}
