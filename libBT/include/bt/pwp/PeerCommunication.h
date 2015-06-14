#ifndef PEERCOMUNICATION_H
#define PEERCOMUNICATION_H

#include "bt/Peer.h"
#include "bt/MetaInfo.h"
#include "bt/ITorrentManager.h"
#include "bt/pwp/HandshakeMessage.h"
#include "bt/pwp/RawMessage.h"
#include "bt/pwp/AMessage.h"

#include <QTcpSocket>

namespace bt{

class Torrent;

class PeerCommunication : public QObject{
public:
    Q_OBJECT

public:
    PeerCommunication(ITorrentManager* manager, PeerPtr peer, const MetaInfo& meta);

    bool sendMessage(const AMessage& message);

signals:
    /**
     * Sent when a new message is received from the client
     */
    void messageReceived(AMessagePtr);

    /**
     * Sent when a successful handshake has occured
     */
    void connectionEstablished();

    /**
     * Sent when a connection with a client is lost
     */
    void connectionLost();

private:
    enum State{
        eSTATE_DISCONNECTED,
        eSTATE_HANDSHAKE,
        eSTATE_MESSAGE
    };

private slots:
    void onConnected();

    void onDisconnected();

    void disconnect();

    void onReadyRead();

private:
    void setState(State state);

private:
    ITorrentManager* mManager;
    PeerPtr mPeer;
    QTcpSocket mSocket;
    const MetaInfo& mMeta;
    State mState;
    RawMessagePtr mCurrentMessage;
    HandshakeMessage mHandshakeMessage;
};

} // bt

#endif // PEERCOMUNICATION_H

