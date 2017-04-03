#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T17:45:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HiOS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    commands.cpp \
    systemmemory.cpp \
    pcbdialog.cpp \
    blocks.cpp \
    hilist.cpp \
    pcbcommands.cpp \
    event.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    commands.h \
    systemmemory.h \
    pcbdialog.h \
    blocks.h \
    hilist.h \
    pcbcommands.h \
    event.h

FORMS    += mainwindow.ui \
    dialog.ui \
    pcbdialog.ui

INCLUDEPATH +=$$_PRO_FILE_PWD_
