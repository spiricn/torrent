#ifndef MESSAGE
#define MESSAGE

#include "bt/pwp/IRawMessage.h"

#include <QIODevice>

namespace bt{

class RawMessage : public IRawMessage {
public:
    enum Id{
        eID_INVALID = -1,
        eID_CHOKE = 0,
        eID_UNCHOKE = 1,
        eID_INTERESTED = 2,
        eID_NOT_INTERESTED = 3,
        eID_HAVE = 4,
        eID_BITFIELD = 5,
        eID_REQUEST = 6,
        eID_PIECE = 7,
        eID_CANCEL = 8,
        eID_PORT = 9,
        eID_MAX
    };

public:
    RawMessage();

    RawMessage(Id id);

    DeserializationStatus deserialize(QIODevice* input);

    bool serialize(QIODevice* output) const;

    quint32 getLengthPrefix() const;

    void writeInt(qint32 value);

    bool readInt(qint32* value);

    Id getId() const;

    void setId(Id id);

    QByteArray& getPayload();

    const QByteArray& getPayload() const;

private:
    qint32 mLengthPrefix;
    Id mId;
    QByteArray mPayload;
};

} // bt

typedef QSharedPointer<bt::RawMessage> RawMessagePtr;

#endif // MESSAGE

