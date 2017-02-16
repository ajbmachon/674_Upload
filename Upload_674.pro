#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T15:39:51
#
#-------------------------------------------------

QT       += core gui network core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Upload_674
TEMPLATE = app


SOURCES += main.cpp\
        upload_674.cpp \
    tagmanager.cpp

HEADERS  += upload_674.h \
    tagmanager.h

FORMS    += upload_674.ui

DISTFILES += \
    Konzept 674 Plugin \
    Konzept 674 Plugin


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += taglib

unix: PKGCONFIG += zlib
