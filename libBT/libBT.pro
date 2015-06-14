#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T17:21:40
#
#-------------------------------------------------

QT -= gui

QT += network

TARGET = BT
TEMPLATE = lib

DEFINES += BT_LIBRARY

SOURCES += \
    source/Info.cpp \
    source/MetaInfo.cpp \
    source/MultipleFileInfo.cpp \
    source/SingleFileInfo.cpp \
    source/TrackerResponse.cpp \
    source/TrackerRequest.cpp \
    source/Utils.cpp \
    source/Peer.cpp \
    source/Torrent.cpp \
    source/TorrentManager.cpp \
    source/Tracker.cpp \
    source/ExternalIPChecker.cpp \
    source/HandshakeMessage.cpp \
    source/PeerCommunication.cpp \
    source/RawMessage.cpp

HEADERS += \
    include/bt/MetaInfo.h \
    include/bt/Info.h \
    include/bt/SingleFileInfo.h \
    include/bt/MultipleFileInfo.h \
    include/bt/Tracker.h \
    include/bt/TrackerResponse.h \
    include/bt/Global.h \
    include/bt/TrackerRequest.h \
    include/bt/Utils.h \
    include/bt/Peer.h \
    include/bt/Torrent.h \
    include/bt/TorrentManager.h \
    include/bt/ITorrentManager.h \
    include/bt/ExternalIPChecker.h \
    include/bt/HandshakeMessage.h \
    include/bt/PeerCommunication.h \
    include/bt/IRawMessage.h \
    include/bt/RawMessage.h \
    include/bt/pwp/HandshakeMessage.h \
    include/bt/pwp/IRawMessage.h \
    include/bt/pwp/PeerCommunication.h \
    include/bt/pwp/RawMessage.h \
    include/bt/pwp/AMessage.h \
    include/bt/pwp/MessageChoke.h \
    include/bt/pwp/MessageHave.h \
    include/bt/pwp/MessageUnchoke.h \
    include/bt/pwp/MessageInterested.h \
    include/bt/pwp/MessageBitfield.h \
    include/bt/pwp/MessageRequest.h \
    include/bt/pwp/MessagePiece.h \
    include/bt/pwp/MessageCancel.h \
    include/bt/pwp/MessagePort.h \
    include/bt/pwp/MessageNotIntereseted.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libBE/release/ -lBE
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libBE/debug/ -lBE
else:unix: LIBS += -L$$OUT_PWD/../libBE/ -lBE


DEPENDPATH += $$PWD/../libBE/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libBE/release/libBE.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libBE/debug/libBE.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libBE/release/BE.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libBE/debug/BE.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libBE/libBE.a

include(Defines.pri)
