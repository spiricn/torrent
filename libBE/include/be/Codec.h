#ifndef CODEC
#define CODEC

#include "be/AObject.h"
#include "be/Global.h"

#include "be/ICodec.h"
#include "priv/IntegerCodec.h"

#include <QFile>

namespace be{

class BE_SHARED_EXPORT Codec : public ICodec {
public:
    bool decode(QList<Token>& tokens, AObjectPtr* output);

    bool encode(const AConstObjectPtr input, QList<Token>& output);

    static IEncoder* getEncoder();

    static IDecoder* getDecoder();

private:
    Codec();

    IDecoder* findDecoder(const QList<Token>& tokens);

    IEncoder* findEncoder(const AConstObjectPtr obj);

    static Codec* getInstance();

private:
    typedef QMap<AObject::Type, QSharedPointer<ICodec>> CodecMap;

private:
    static Codec* sInstance;

    CodecMap mCodecs;
};

} // be

#endif // CODEC

