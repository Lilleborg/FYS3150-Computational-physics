TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    odesolver.cpp \
    population/susceptibles.cpp \
    population/infected.cpp \
    population/recovered.cpp \
    population/a_parameter.cpp \
    population/a_constant.cpp \
    population/a_seasons.cpp \
    problem.cpp \
    population/population_group.cpp \
    writeme.cpp

HEADERS += \
    odesolver.h \
    population/susceptibles.h \
    population/infected.h \
    population/recovered.h \
    population/a_seasons.h \
    problem.h \
    population/a_constant.h \
    population/a_parameter.h \
    population/population_group.h \
    writeme.h
