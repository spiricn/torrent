#ifndef BENCODESTRING
#define BENCODESTRING

#include "AObject.h"
#include "be/Global.h"

#include <QByteArray>
#include <QSharedPointer>
#include <QDebug>

namespace be{

class BE_SHARED_EXPORT String : public AObject{
public:
    String(const QByteArray& value);

    QByteArray& getValue();

    const QByteArray& getValue() const;

    QString toString() const;
private:
    QByteArray mValue;
};

typedef QSharedPointer<String> StringPtr;

} // be

#endif // BENCODESTRING

