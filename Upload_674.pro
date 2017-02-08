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

QMAKE_LFLAGS_WINDOWS += -static-libgcc -static-libstdc++ -static

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../taglib-1.11.1/taglib/release/ -ltag
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../taglib-1.11.1/taglib/debug/ -ltag
else:unix: LIBS += -L$$PWD/../../../taglib-1.11.1/taglib/ -ltag

INCLUDEPATH += $$PWD/../../../taglib-1.11.1
INCLUDEPATH += $$PWD/../../../taglib-1.11.1/taglib/toolkit
INCLUDEPATH += $$PWD/../../../taglib-1.11.1/taglib
DEPENDPATH += $$PWD/../../../taglib-1.11.1

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../taglib-1.11.1/taglib/release/libtag.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../taglib-1.11.1/taglib/debug/libtag.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../taglib-1.11.1/taglib/release/tag.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../taglib-1.11.1/taglib/debug/tag.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../taglib-1.11.1/taglib/libtag.a
