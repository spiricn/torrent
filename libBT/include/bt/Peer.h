#ifndef PEER
#define PEER

#include <be/Dictionary.h>

#include <QHostAddress>

#include "bt/Global.h"

namespace bt{

class BT_SHARED_EXPORT Peer{
public:
    typedef quint64 Id;

public:
    Peer(be::DictionaryPtr peerDict);

    Peer(const QByteArray& peerInfo);

    bool parse();

    const QByteArray& getPeerId() const;

    const QHostAddress& getIP() const;

    Id getId() const;

    quint16 getPort() const;

private:
    QByteArray mPeerId;
    QHostAddress mAddress;
    quint16 mPort;
    be::DictionaryPtr mDict;
    QByteArray mInfo;
    Id mId;
};

typedef QSharedPointer<Peer> PeerPtr;

} // be

#endif // PEER

