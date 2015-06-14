#ifndef MESSAGEPORT
#define MESSAGEPORT

#include "bt/pwp/AMessage.h"

namespace bt{

class MessagePort : public AMessage{
public:
    MessagePort(qint32 port) : AMessage(RawMessage::eID_PORT), mPort(port){
    }

    bool deserialize(RawMessagePtr input){
        if(!AMessage::deserialize(input)){
            return false;
        }

        if(!input->readInt(&mPort)){
            return false;
        }

        return true;
    }

    bool serialize(RawMessage* output) const{
        if(!AMessage::serialize(output)){
            return false;
        }

        output->writeInt(mPort);

        return true;
    }

    qint32 getPort() const{
        return mPort;
    }

private:
    qint32 mPort;
};

} // bt

#endif // MESSAGEPORT

