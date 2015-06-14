#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T18:41:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MetaInfoWidget.cpp

HEADERS  += MainWindow.h \
    MetaInfoWidget.h

FORMS    += MainWindow.ui \
    MetaInfoWidget.ui


######################################################################################
# libBE

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libBE/release/ -lBE
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libBE/debug/ -lBE
else:unix: LIBS += -L$$OUT_PWD/../libBE/ -lBE


DEPENDPATH += $$PWD/../libBE
include($$PWD/../libBT/Defines.pri)

######################################################################################
# libBT

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libBT/release/ -lBT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libBT/debug/ -lBT
else:unix: LIBS += -L$$OUT_PWD/../libBT/ -lBT

DEPENDPATH += $$PWD/../libBT
include($$PWD/../libBT/Defines.pri)

######################################################################################
