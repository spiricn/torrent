#ifndef MESSAGEINTERESTED
#define MESSAGEINTERESTED


#include "bt/pwp/AMessage.h"

namespace bt{

class MessageInterested : public AMessage{
public:
    MessageInterested() : AMessage(RawMessage::eID_INTERESTED){
    }
};

} // bt

#endif // MESSAGEINTERESTED

