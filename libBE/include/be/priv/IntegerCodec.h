#ifndef INTEGERCODEC
#define INTEGERCODEC

#include "be/ICodec.h"

namespace be{

class IntegerCodec : public ICodec {
public:
    bool decode(QList<Token>& tokens, AObjectPtr* output);

    bool encode(const AConstObjectPtr input, QList<Token>& output);
};

} // be

#endif // INTEGERCODEC

