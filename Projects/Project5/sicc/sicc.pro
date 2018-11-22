TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    populations.cpp \
    odesolver.cpp \
    vec3.cpp

HEADERS += \
    populations.h \
    odesolver.h \
    vec3.h
