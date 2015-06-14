#include "be/AObject.h"

#include <QDebug>

namespace be{

AObject::AObject(Type type) : mType(type){
}

AObject::~AObject(){
}

AObject::Type AObject::getType() const{
    return mType;
}

} // be

QDebug operator<<(QDebug d, be::AObjectPtr obj){
    return d << obj->toString();
}

