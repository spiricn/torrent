#ifndef MESSAGEUNCHOKE
#define MESSAGEUNCHOKE

#include "bt/pwp/AMessage.h"

namespace bt{

class MessageUnchoke : public AMessage{
public:
    MessageUnchoke() : AMessage(RawMessage::eID_UNCHOKE){
    }
};

} // bt

#endif // MESSAGEUNCHOKE

