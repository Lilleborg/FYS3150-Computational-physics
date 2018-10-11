TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    vec3.cpp \
    euler.cpp \
    planetaryobject.cpp \
    solarsystem.cpp

HEADERS += \
    vec3.h \
    euler.h \
    planetaryobject.h \
    solarsystem.h
