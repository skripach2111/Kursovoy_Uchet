QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorization_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    moreaboutinvoice_dialog.cpp

HEADERS += \
    authorization_dialog.h \
    mainwindow.h \
    moreaboutinvoice_dialog.h

FORMS += \
    authorization_dialog.ui \
    mainwindow.ui \
    moreaboutinvoice_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
