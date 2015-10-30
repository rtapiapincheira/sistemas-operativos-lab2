TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MAC_SDK = macosx10.11

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    \
    src/Exception.cpp \
    src/Mutex.cpp \
    src/Thread.cpp \
    src/Utils.cpp

HEADERS += \
    include/Exception.h \
    include/Mutex.h \
    include/Thread.h \
    include/Utils.h
