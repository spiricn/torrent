#include "be/Dictionary.h"
#include "be/Codec.h"

namespace be{

Dictionary::Dictionary() : AObject(eTYPE_DICTIONARY){
}

Dictionary::ObjectMap& Dictionary::getValue(){
    return mValue;
}

const Dictionary::ObjectMap& Dictionary::getValue() const{
    return mValue;
}

bool Dictionary::getString(const QString& key, QByteArray* res){
    AObjectPtr obj = getObject(key);

    if(obj != NULL && obj->getType() == AObject::eTYPE_STRING){
        *res = dynamic_cast<String*>(obj.data())->getValue();

        return true;
    }

    return false;
}

bool Dictionary::getString(const QString& key, QString* res){
    QByteArray byteArray;

    if(getString(key, &byteArray)){
        *res = QString(byteArray);

        return true;
    }
    else{
        return false;
    }
}

bool Dictionary::getInteger(const QString& key, qint32* res){
    AObjectPtr obj = getObject(key);

    if(obj != NULL && obj->getType() == AObject::eTYPE_INTEGER){
        *res = dynamic_cast<Integer*>(obj.data())->getValue();

        return true;
    }

    return false;
}

bool Dictionary::getList(const QString& key, List::ObjectList** res){
    AObjectPtr obj = getObject(key);

    if(obj != NULL && obj->getType() == AObject::eTYPE_LIST){
        *res = &dynamic_cast<List*>(obj.data())->getValue();

        return true;
    }

    return false;
}

bool Dictionary::getDictionary(const QString& key, DictionaryPtr* res){
    AObjectPtr obj = getObject(key);

    if(obj != NULL && obj->getType() == AObject::eTYPE_DICTIONARY){
        *res = obj.dynamicCast<Dictionary>();

        return true;
    }

    return false;
}

AObjectPtr Dictionary::getObject(const QString& key){
    for(ObjectMap::iterator iter=mValue.begin(); iter!=mValue.end(); iter++){
        if(key.compare(iter.key()->getValue()) == 0){
            return iter.value();
        }
    }

    return AObjectPtr(NULL);
}

bool Dictionary::contains(const QString& key) const{
    return const_cast<Dictionary*>(this)->getObject(key) != NULL;
}

QString Dictionary::toString() const{
    QString res = "{\n";

    for(be::Dictionary::ObjectMap::const_iterator iter=getValue().cbegin(); iter!=getValue().cend(); iter++){
        res += iter.key()->toString();

        res += " : ";

        res += iter.value()->toString();

        res += " , \n";
    }

    res += "}";

    return res;
}

} // be

QDebug operator << (QDebug d, const be::Dictionary& dict){
    d << "{";

    for(be::Dictionary::ObjectMap::const_iterator iter=dict.getValue().cbegin(); iter!=dict.getValue().cend(); iter++){
        be::StringPtr key = iter.key();

        be::AObjectPtr value = iter.key();

        switch(value->getType()){
            case be::AObject::eTYPE_STRING:
                break;
            case be::AObject::eTYPE_INTEGER:
                break;
            case be::AObject::eTYPE_DICTIONARY:
                break;
            case be::AObject::eTYPE_LIST:
                break;
        }
    }

    d << "}";

    return d;
}
