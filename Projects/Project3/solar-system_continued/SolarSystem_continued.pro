TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CFLAGS += -march=native -O3
#QMAKE_CXXFLAGS += -march=native -O3
#QMAKE_CXXFLAGS_RELEASE += -march=native -O3

SOURCES += main.cpp \
    celestialbody.cpp \
    solarsystem.cpp \
    vec3.cpp \
    solver.cpp

HEADERS += \
    celestialbody.h \
    solarsystem.h \
    vec3.h \
    solver.h

