#ifndef DICTIONARYCODEC
#define DICTIONARYCODEC

#include "be/ICodec.h"

namespace be{

class DictionaryCodec : public ICodec {
public:
    bool decode(QList<Token>& tokens, AObjectPtr* output);

    bool encode(const AConstObjectPtr input, QList<Token>& output);
};

} // be

#endif // DICTIONARYCODEC
