TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
INCLUDEPATH += /usr/local/Cellar/armadillo/9.100.5/include/
LIBS += -L/usr/local/Cellar/armadillo/9.100.5/lib/ -larmadillo
