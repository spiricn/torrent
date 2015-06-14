#ifndef BENCODEINTEGER
#define BENCODEINTEGER

#include "AObject.h"
#include "be/Global.h"

#include <QSharedPointer>
#include <QDebug>

namespace be{

class BE_SHARED_EXPORT Integer : public AObject{
public:
    Integer(qint32 value);

    qint32 getValue() const;

    QString toString() const;

private:
    qint32 mValue;
};

typedef QSharedPointer<Integer> IntegerPtr;

} // be

#endif // BENCODEINTEGER

