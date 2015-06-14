#ifndef MESSAGENOTINTERESTED
#define MESSAGENOTINTERESTED

#include "bt/pwp/AMessage.h"

namespace bt{

class MessageNotInterested : public AMessage{
public:
    MessageNotInterested() : AMessage(RawMessage::eID_NOT_INTERESTED){
    }
};

} // bt

#endif // MESSAGENOTINTERESTED

