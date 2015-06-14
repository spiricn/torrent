#ifndef IMESSAGE
#define IMESSAGE

#include "bt/pwp/RawMessage.h"

namespace bt{

class AMessage{
public:
    AMessage(RawMessage::Id id) : mId(id){
    }

    virtual bool deserialize(RawMessagePtr){
        return true;
    }

    virtual bool serialize(RawMessage* output) const{
        output->setId(mId);

        return true;
    }

    RawMessage::Id getType() const{
        return mId;
    }

    virtual ~AMessage(){
    }

private:
    RawMessage::Id mId;
};

} // bt

typedef QSharedPointer<bt::AMessage> AMessagePtr;

#endif // IMESSAGE

