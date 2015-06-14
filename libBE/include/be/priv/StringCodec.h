#ifndef STRINGCODEC
#define STRINGCODEC

#include "be/ICodec.h"

namespace be{

class StringCodec : public ICodec {
public:
    bool decode(QList<Token>& tokens, AObjectPtr* output);

    bool encode(const AConstObjectPtr input, QList<Token>& output);
};

} // be

#endif // STRINGCODEC
