QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = $$PWD/../bin

include($$PWD/cell/librarymgr.pri)
include($$PWD/lib/lib.pri)

RESOURCES += \
    resource/res.qrc

RC_FILE = $$PWD/resource/app.rc

DISTFILES += \
    resource/lib.jpg
