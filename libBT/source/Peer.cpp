#include "bt/Peer.h"

#define PEER_ID_KEY "peer id"
#define IP_KEY "ip"
#define PORT_KEY "port"
#define BYTES_PEER_IP ( 4 )
#define BYTES_PEER_PORT ( 2 )

namespace bt{

Peer::Peer(be::DictionaryPtr peerDict) : mDict(peerDict){
}

Peer::Peer(const QByteArray& peerInfo) : mInfo(peerInfo){
}

bool Peer::parse(){
    if(mDict != NULL){
        // Dictionary model
        if(!mDict->getString(PEER_ID_KEY, &mPeerId)){
            qDebug() << PEER_ID_KEY " missing from peer dictionary";

            return false;
        }

        QByteArray ipStr;

        if(!mDict->getString(IP_KEY, &ipStr)){
            qDebug() << IP_KEY " missing from peer dictionary";

            return false;
        }

        mAddress = QHostAddress(QString(ipStr));

        qint32 port;

        if(!mDict->getInteger(PORT_KEY, &port)){
            qDebug() << PORT_KEY " missing from peer dictionary";

            return false;
        }

        mPort = static_cast<quint16>(port);

        mDict.clear();
    }
    else{
        // Binary model
        if(mInfo.size() != (BYTES_PEER_IP + BYTES_PEER_PORT)){
            qDebug() << "Malformed peer binary info";
            return false;
        }

        QByteArray ip = mInfo.mid(0, BYTES_PEER_IP);

        QDataStream ipDs(ip);

        qint32 ipv4Ip;

        ipDs >> ipv4Ip;

        mAddress = QHostAddress(ipv4Ip);

        QByteArray port = mInfo.mid(BYTES_PEER_IP, BYTES_PEER_IP + BYTES_PEER_PORT);

        QDataStream portDs(port);

        portDs >> mPort;
    }

    // Calculate unique ID
    // [2] [      4     ] [  2   ]
    // [0] [ ip address ] [ port ]

    mId = (mAddress.toIPv4Address() << 4) | mPort;

    return true;
}

const QByteArray& Peer::getPeerId() const{
    return mPeerId;
}

const QHostAddress& Peer::getIP() const{
    return mAddress;
}

Peer::Id Peer::getId() const{
    return mId;
}
quint16 Peer::getPort() const{
    return mPort;
}

} // be
