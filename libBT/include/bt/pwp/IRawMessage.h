#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QIODevice>

namespace bt{

class IRawMessage{
public:
    enum DeserializationStatus{
        eSTATUS_OK,
        eSTATUS_INCOMPLETE,
        eSTATUS_ERROR
    };

public:
    virtual ~IRawMessage(){
    }

    virtual DeserializationStatus deserialize(QIODevice* input) = 0;

    virtual bool serialize(QIODevice* output) const = 0;
};

} // bt

#endif // IMESSAGE_H

