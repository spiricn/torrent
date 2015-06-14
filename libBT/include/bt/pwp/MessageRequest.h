#ifndef MESSAGEREQUEST
#define MESSAGEREQUEST

#include "bt/pwp/AMessage.h"

namespace bt{

class MessageRequest : public AMessage{
public:
    MessageRequest(qint32 index=-1, qint32 begin=-1, qint32 length=-1) : AMessage(RawMessage::eID_REQUEST), mIndex(index),
        mBegin(begin), mLength(length){
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

        if(!input->readInt(&mLength)){
            return false;
        }

        return true;
    }

    bool serialize(RawMessage* output) const{
        if(!AMessage::serialize(output)){
            return false;
        }

        output->writeInt(mIndex);
        output->writeInt(mBegin);
        output->writeInt(mLength);

        return true;
    }

    qint32 getIndex() const{
        return mIndex;
    }

    qint32 getBegin() const{
        return mBegin;
    }

    qint32 getLength() const{
        return mLength;
    }

private:
    qint32 mIndex;
    qint32 mBegin;
    qint32 mLength;
};

} // bt

#endif // MESSAGEREQUEST

