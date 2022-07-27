QT       += core gui
QT       += network
QT       += websockets
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    websocketclinet.cpp \
    helpers.cpp \
    callapi.cpp \
    driverhelper.cpp \
    login.cpp \
    qmessage.cpp \
    sqliteutil.cpp

HEADERS += \
    ICReader.h \
    mainwindow.h \
    websocketclinet.h \
    helpers.h \
    callapi.h \
    driverhelper.h \
    login.h \
    qmessage.h \
    sqliteutil.h

FORMS += \
    mainwindow.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
#LIBS +=\ICReader.lib
LIBS +=ICReader.lib
DISTFILES += \
    ICReader.lib \
    config.ini \
    FaceBackgroup.png
