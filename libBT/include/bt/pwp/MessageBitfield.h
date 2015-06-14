#ifndef MESSAGEBITFIELD
#define MESSAGEBITFIELD

#include "bt/pwp/AMessage.h"

namespace bt{

class MessageBitfield : public AMessage{
public:
    MessageBitfield() : AMessage(RawMessage::eID_BITFIELD){
    }

    const QByteArray& getBitfield() const{
        return mBitfield;
    }

    bool deserialize(RawMessagePtr input){
        if(!AMessage::deserialize(input)){
            return false;
        }

        mBitfield = input->getPayload();

        return true;
    }

    bool serialize(RawMessage* output) const{
        if(!AMessage::serialize(output)){
            return false;
        }

        output->getPayload() = mBitfield;

        return true;
    }

private:
    QByteArray mBitfield;
};

} // bt

#endif // MESSAGEBITFIELD

