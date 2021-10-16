QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aircraft.cpp \
    commandpost.cpp \
    main.cpp \
    mainwindow.cpp \
    missile.cpp \
    rls.cpp \
    target.cpp \
    tsimulator.cpp

HEADERS += \
    PosObject.h \
    TPoint.h \
    aircraft.h \
    commandpost.h \
    mainwindow.h \
    missile.h \
    rls.h \
    target.h \
    tsimulator.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Lr_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT += sql
