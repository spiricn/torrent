#ifndef HANDSHAKEMESSAGE
#define HANDSHAKEMESSAGE

#include "bt/pwp/IRawMessage.h"

#include <QIODevice>

#define RESERVED_BYTES_SIZE ( 8 )

namespace bt{

class HandshakeMessage : public IRawMessage{
public:
    HandshakeMessage();

    HandshakeMessage(const QByteArray& pstr, const QByteArray& infoHash, const QByteArray& peerId);

    bool serialize(QIODevice* output) const;

    DeserializationStatus deserialize(QIODevice* input);

    const QByteArray& getPstr() const;

    const char* getReserved() const;

    const QByteArray& getInfoHash() const;

    const QByteArray& getPeerId() const;

private:
    QByteArray mPstr;
    char mReserved[RESERVED_BYTES_SIZE];
    QByteArray mInfoHash;
    QByteArray mPeerId;
};

} // bt

#endif // HANDSHAKEMESSAGE
