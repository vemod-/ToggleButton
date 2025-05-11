!contains(PROFILES,$$_FILE_){
PROFILES+=$$_FILE_

INCLUDEPATH += $$PWD

SOURCES += $$PWD/qtogglebutton.cpp

HEADERS  += $$PWD/qtogglebutton.h
}
