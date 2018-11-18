TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

SOURCES += \
        main.cpp \
    functions.cpp \
    exercises.cpp

HEADERS += \
    functions.h \
    exercises.h

INCLUDEPATH += /usr/local/Cellar/armadillo/9.100.5_1/include/
LIBS += -L/usr/local/Cellar/armadillo/9.100.5_1/lib/ -larmadillo
