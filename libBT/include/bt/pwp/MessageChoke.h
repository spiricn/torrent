#ifndef MESSAGECHOKE
#define MESSAGECHOKE

#include "bt/pwp/AMessage.h"

namespace bt{

class MessageChoke : public AMessage{
public:
    MessageChoke() : AMessage(RawMessage::eID_CHOKE){
    }
};
}
#endif // MESSAGECHOKE

