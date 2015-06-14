#ifndef MESSAGEPIECE
#define MESSAGEPIECE

#include "bt/pwp/AMessage.h"

#include <QByteArray>

namespace bt{

class MessagePiece : public AMessage{
public:
    MessagePiece() : AMessage(RawMessage::eID_PIECE){
    }

    MessagePiece(qint32 index, qint32 begin, const QByteArray& block) : AMessage(RawMessage::eID_PIECE),
        mBegin(begin), mIndex(index), mBlock(block){
    }

    bool deserialize(RawMessagePtr input){
        if(!AMessage::deserialize(input)){
            return false;
        }

        if(!input->readInt(&mIndex)){
            return false;
        }

        if(!input->readInt(&mBegin)){
            return false;
        }

        mBlock = input->getPayload().mid(2*sizeof(quint32), input->getPayload().size() - 2*sizeof(quint32));

        return true;
    }

    bool serialize(RawMessage* output) const{
        if(!AMessage::serialize(output)){
            return false;
        }

        output->writeInt(mIndex);
        output->writeInt(mBegin);

        output->getPayload().append(mBlock);

        return true;
    }

    qint32 getIndex() const{
        return mIndex;
    }

    qint32 getBegin() const{
        return mBegin;
    }

    const QByteArray& getBlock() const{
        return mBlock;
    }

private:
    qint32 mIndex;
    qint32 mBegin;
    QByteArray mBlock;
};

} // bt

#endif // MESSAGEPIECE

