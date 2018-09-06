TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -march=native -O3
QMAKE_CXXFLAGS += -march=native -O3
QMAKE_CXXFLAGS_RELEASE += -march=native -O3

SOURCES += \
        main.cpp
INCLUDEPATH += /usr/local/Cellar/armadillo/9.100.5/include/
LIBS += -L/usr/local/Cellar/armadillo/9.100.5/lib/ -larmadillo
