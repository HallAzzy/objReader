!CAMERA_PRI {
CONFIG += CAMERA_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)

HEADERS += \
	$$PWD/camera.h
	
SOURCES += \
	$$PWD/camera.cpp
}
