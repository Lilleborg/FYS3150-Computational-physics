TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    population/populations.cpp \
    odesolver.cpp \
    vec3.cpp \
    population/susceptibles.cpp \
    population/infected.cpp \
    population/recovered.cpp \
    population/a_parameter.cpp \
    population/a_constant.cpp \
    population/a_seasons.cpp \
    problem.cpp \
    population/population_group.cpp

HEADERS += \
    population/populations.h \
    odesolver.h \
    vec3.h \
    population/susceptibles.h \
    population/infected.h \
    population/recovered.h \
    population/a_seasons.h \
    problem.h \
    population/a_constant.h \
    population/a_parameter.h \
    population/population_group.h
