#include "be/String.h"

namespace be{

String::String(const QByteArray& value) : AObject(eTYPE_STRING), mValue(value){
}

QByteArray& String::getValue(){
    return mValue;
}

const QByteArray& String::getValue() const{
    return mValue;
}

QString String::toString() const{
    return QString("'%1'").arg(QString(mValue));
}

} // be

