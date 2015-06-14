#ifndef IENCODER
#define IENCODER

#include "be/AObject.h"
#include "be/Token.h"
#include "be/Global.h"

#include <QIODevice>
#include <QByteArray>
#include <QString>

namespace be{

class BE_SHARED_EXPORT IEncoder{
public:
    virtual ~IEncoder();

    virtual bool encode(const AConstObjectPtr input, QList<Token>& output) = 0;

    bool encode(const AConstObjectPtr input, QByteArray* output);

    bool encode(const AConstObjectPtr input, QIODevice* output);

    bool encodeFile(const AConstObjectPtr input, const QString& outputFilePath);
};

} // be

#endif // IENCODER

