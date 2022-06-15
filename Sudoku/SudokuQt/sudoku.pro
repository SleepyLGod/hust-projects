#-------------------------------------------------
#
# Project created by QtCreator 2021-09-09 T10:31:04
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    mainwindow.cpp \
    cnf.cpp \
    dpll.cpp \
    main.cpp \
    sudoku.cpp

HEADERS += \
    mainwindow.h \
    cnf.h \
    dpll.h \
    sudoku.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

