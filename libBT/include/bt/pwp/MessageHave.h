#ifndef MESSAGEHAVE
#define MESSAGEHAVE

#include "bt/pwp/AMessage.h"

namespace bt{

class MessageHave : public AMessage{
public:
    MessageHave(qint32 pieceIndex=-1) : AMessage(RawMessage::eID_HAVE), mPieceIndex(pieceIndex){
    }

    qint32 getPieceIndex() const{
        return mPieceIndex;
    }

    bool deserialize(RawMessagePtr input){
        if(!AMessage::deserialize(input)){
            return false;
        }

        if(!input->readInt(&mPieceIndex)){
            return false;
        }

        return true;
    }

    bool serialize(RawMessage* output) const{
        if(!AMessage::serialize(output)){
            return false;
        }

        output->writeInt(mPieceIndex);

        return true;
    }

private:
    qint32 mPieceIndex;
};

} // bt

#endif // MESSAGEHAVE

