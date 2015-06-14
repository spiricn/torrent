#include "be/List.h"

namespace be{

List::List() : AObject(eTYPE_LIST){
}

List::ObjectList& List::getValue(){
    return mValue;
}

const List::ObjectList& List::getValue() const{
    return mValue;
}

QString List::toString() const{
    QString res = "[";

    for(be::List::ObjectList::const_iterator iter=getValue().cbegin(); iter!=getValue().cend(); iter++){
        res += (*iter)->toString() + " , ";
    }

    res += "]";

    return res;
}

} // be
