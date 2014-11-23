#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T10:10:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniGA
TEMPLATE = app


SOURCES += main.cpp\
        janela.cpp \
    plotarea.cpp \
    doubleslider.cpp \
    bomba.cpp \
    che.cpp \
    material.cpp \
    ponto.cpp \
    pontohq.cpp \
    reservatorio.cpp \
    rho.cpp \
    tau.cpp \
    tubo.cpp \
    valvula.cpp \
    valvuladeretencao.cpp \
    ventosa.cpp

HEADERS  += janela.h \
    plotarea.h \
    doubleslider.h \
    bomba.hpp \
    che.hpp \
    constantes.hpp \
    funcoes.hpp \
    headers.hpp \
    malha.hpp \
    material.hpp \
    ponto.hpp \
    pontohq.hpp \
    reservatorio.hpp \
    rho.hpp \
    tau.hpp \
    tubo.hpp \
    valvula.hpp \
    valvuladeretencao.hpp \
    ventosa.hpp


FORMS    += janela.ui
