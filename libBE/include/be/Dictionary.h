#ifndef BENCODEDICTIONARY
#define BENCODEDICTIONARY

#include "AObject.h"
#include "String.h"
#include "Integer.h"
#include "List.h"
#include "be/Global.h"
#include <QSharedPointer>
#include <QMap>
#include <QDebug>

namespace be{

class Dictionary;

typedef QSharedPointer<Dictionary> DictionaryPtr;

class BE_SHARED_EXPORT Dictionary : public AObject{
public:
    typedef QSharedPointer<String> Key;

    typedef QSharedPointer<AObject> Value;

    typedef QMap<Key, Value> ObjectMap;

public:
    Dictionary();

    ObjectMap& getValue();

    bool getString(const QString& key, QByteArray* res);

    bool getString(const QString& key, QString* res);

    bool getInteger(const QString& key, qint32* res);

    bool getList(const QString& key, List::ObjectList** res);

    bool getDictionary(const QString& key, DictionaryPtr* res);

    AObjectPtr getObject(const QString& key);

    const ObjectMap& getValue() const;

    bool contains(const QString& key) const;

    QString toString() const;

private:
    Q_DISABLE_COPY(Dictionary)

private:
    ObjectMap mValue;
};

} // be

#endif // BENCODEDICTIONARY

