#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T17:57:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    helpdialog.cpp \
    loaddialog.cpp

HEADERS  += mainwindow.h \
    helpdialog.h \
    loaddialog.h

FORMS    += mainwindow.ui \
    helpdialog.ui \
    loaddialog.ui

DISTFILES += \
    Division.txt \
    Division.txt \
    MaxNumber.txt \
    Shifting.txt \
    Absolute.txt \
    Bootstrap.txt

RESOURCES += \
    myres.qrc

ICON = EmulatorIcon.icns
