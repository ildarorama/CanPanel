#-------------------------------------------------
#
# Project created by QtCreator 2017-06-13T21:20:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTest1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the fosllowing line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DEPENDPATH += /usr/lib
LIBS += -lzmq -lboost_system -lboost_thread -lprotobuf

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    numpaddialog.cpp \
    passworddialog.cpp \
    message.pb.cc \
    selectcodedialog.cpp \
    codeitem.cpp \
    zmqworkerthread.cpp \
    telemetrybean.cpp

HEADERS += \
        mainwindow.h \
    numpaddialog.h \
    passworddialog.h \
    message.pb.h \
    selectcodedialog.h \
    codeitem.h \
    zmqworkerthread.h \
    telemetrybean.h

FORMS += \
        mainwindow.ui \
    numpaddialog.ui \
    passworddialog.ui \
    selectcodedialog.ui

linux-* {
target.path = /tmp
INSTALLS += target

}
