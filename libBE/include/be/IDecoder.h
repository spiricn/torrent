#ifndef IDECODER
#define IDECODER

#include <QList>

#include "be/AObject.h"

#include "be/Token.h"
#include "be/Global.h"

namespace be{

class BE_SHARED_EXPORT IDecoder{
public:
    virtual ~IDecoder();

    virtual bool decode(QList<Token>& tokens, AObjectPtr* output) = 0;

    bool decode(QIODevice *input, AObjectPtr* output);

    bool decodeFile(const QString& filePath, AObjectPtr* output);

    bool decode(const QByteArray& string, AObjectPtr* output);
};

} // be

#endif // IDECODER

