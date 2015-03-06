#-------------------------------------------------
#
# Project created by QtCreator 2015-03-01T18:51:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pcsx2interface
TEMPLATE = app


SOURCES += main.cpp\
        pcsxwindow.cpp \
    filemanager.cpp \
    pcsxlabel.cpp

HEADERS  += pcsxwindow.h \
    filemanager.h \
    pcsxlabel.h

FORMS    +=

RESOURCES += \
    ressources.qrc
