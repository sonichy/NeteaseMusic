QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeteaseMusic
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    titlebar.cpp \
    controlbar.cpp \
    navwidget.cpp \
    apimusic.cpp \
    toplistitem.cpp

HEADERS += \
        mainwindow.h \
    titlebar.h \
    controlbar.h \
    navwidget.h \
    apimusic.h \
    toplistitem.h

RESOURCES += \
    res.qrc
