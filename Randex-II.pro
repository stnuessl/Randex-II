#-------------------------------------------------
#
# Project created by QtCreator 2013-03-04T15:01:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Randex-II
TEMPLATE = app


SOURCES += src/main.cpp\
        src/randex.cpp \
    src/scheduleview.cpp

HEADERS  += src/randex.h \
    src/scheduleview.h

FORMS    += randex.ui

OTHER_FILES += \
    LICENSE \
    README
