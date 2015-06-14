#include "priv/IntegerNode.h"

#include "be/Integer.h"

namespace be{

IntegerNode::IntegerNode(IParser* parent) : ANode(eTYPE_INTEGER, parent){
}

AObjectPtr IntegerNode::parse(QList<Token>& tokens){

}

} // be
