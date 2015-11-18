TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MAC_SDK = macosx10.11

INCLUDEPATH += cpp/include

SOURCES += \
    cpp/src/main.cpp \
    \
    cpp/src/SolverThread.cpp \
    cpp/src/Thread.cpp

HEADERS += \
    cpp/include/Function.h \
    cpp/include/SolverThread.h \
    cpp/include/Thread.h
