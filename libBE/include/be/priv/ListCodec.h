#ifndef LISTCODEC
#define LISTCODEC

#include "be/ICodec.h"

namespace be{

class ListCodec : public ICodec {
public:
    bool decode(QList<Token>& tokens, AObjectPtr* output);

    bool encode(const AConstObjectPtr input, QList<Token>& output);
};

} // be

#endif // LISTCODEC
