#ifndef ABENCODEOBJECT
#define ABENCODEOBJECT

#include "be/Global.h"

#include <QSharedPointer>
#include <QIODevice>

namespace be{

class BE_SHARED_EXPORT AObject {
public:
    enum Type{
        eTYPE_INVALID,
        eTYPE_STRING,
        eTYPE_INTEGER,
        eTYPE_LIST,
        eTYPE_DICTIONARY,
        eTYPE_MAX
    };

public:
    AObject(Type type);

    virtual ~AObject();

    Type getType() const;

    virtual QString toString() const = 0;

private:
    Type mType;
};

typedef QSharedPointer<AObject> AObjectPtr;

typedef QSharedPointer<const AObject> AConstObjectPtr;

} // be

QDebug BE_SHARED_EXPORT operator<<(QDebug d, be::AObjectPtr obj);

#endif // ABENCODEOBJECT

