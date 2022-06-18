#-------------------------------------------------
#
# Project created by QtCreator 2020-02-18T10:10:06
#
#-------------------------------------------------

QT       += core gui
QT       += network
QMAKE_CXXFLAGS += -std=c++0x
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#this func is used by whang jian, in opti tarck moudle
QT       += datavisualization
QT       += charts
QT       += 3dcore
TARGET = Polish_Climbot
TEMPLATE = app
INCLUDEPATH+=D:/eigen-3.4.0
QT       += core gui serialport 3dextras 3dinput 3dcore 3drender
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    auxiliatyentity.cpp \
    axesentity.cpp \
    axesentity_robot.cpp \
    dobotmodel.cpp \
    lineentity.cpp \
        main.cpp \
    connectrobot.cpp \
    ClimbotWin.cpp \
    dataview.cpp \
    panel.cpp \
    trajectory.cpp

HEADERS += \
    ClimbotWin.h \
    auxiliatyentity.h \
    axesentity.h \
    axesentity_robot.h \
    connectrobot.h \
    dobotmodel.h \
    filepath.h \
    lineentity.h \
    panel.h \
    trajectory.h

FORMS += \
    ClimbotWin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc

RC_ICONS = robot.ico

DISTFILES += \
    fan_data.txt \
    model/WindBlade.obj \
    model/base.obj \
    myqss.qss \
    optitrack_data.txt \
    setting.json
