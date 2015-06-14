#include "be/Integer.h"

namespace be{

Integer::Integer(qint32 value) : AObject(eTYPE_INTEGER), mValue(value){
}

qint32 Integer::getValue() const {
    return mValue;
}

QString Integer::toString() const{
    return QString::number(mValue);
}

} // be
