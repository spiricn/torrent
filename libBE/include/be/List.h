#ifndef BENCODELIST
#define BENCODELIST

#include "AObject.h"
#include "be/Global.h"

#include <QSharedPointer>
#include <QList>
#include <QDebug>

namespace be{

class BE_SHARED_EXPORT List : public AObject{
public:
    typedef QList<AObjectPtr> ObjectList;

public:
    List();

    ObjectList& getValue();

    const ObjectList& getValue() const;

    QString toString() const;

private:
    ObjectList mValue;
};

typedef QSharedPointer<List> ListPtr;

} // be

#endif // BENCODELIST

