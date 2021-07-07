TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        binarysearchtree.cpp \
        main.cpp \
        node.cpp

HEADERS += \
    binarysearchtree.h \
    mathedealer.h \
    node.h

DISTFILES += \
    dumped.txt
