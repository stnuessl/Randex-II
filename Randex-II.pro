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
    src/scheduletable.cpp \
    src/aboutrandex.cpp

HEADERS  += src/randex.h \
    src/scheduletable.h \
    src/aboutrandex.h

FORMS    += src/randex.ui \
    src/scheduletable.ui \
    src/aboutrandex.ui

OTHER_FILES += \
    LICENSE \
    README
