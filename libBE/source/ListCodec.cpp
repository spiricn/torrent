#include "be/priv/ListCodec.h"

#include "be/List.h"

#include "be/Codec.h"

namespace be{

bool ListCodec::decode(QList<Token>& tokens, AObjectPtr* output){
    ListPtr obj = ListPtr(new List);

    // Sanity check
    Q_ASSERT(!tokens.empty() && tokens[0].getType() == Token::eTYPE_LIST_START);

    // Consume list start token
    tokens.pop_front();

    while(true){
        if(tokens.empty()){
            qDebug() << "Ran out of tokens while parsing list";

            return false;
        }

        if(tokens[0].getType() == Token::eTYPE_ELEMENT_END){
            // Reached the end of the list
            tokens.pop_front();
            break;
        }

        AObjectPtr listElement;

        // Decode next list element
        if(!Codec::getDecoder()->decode(tokens, &listElement)){
            return false;
        }

        // Add it to our list
        obj->getValue().push_back(listElement);
    }

    *output = obj;

    return true;
}

bool ListCodec::encode(const AConstObjectPtr input, QList<Token>& output){
    const List* list = dynamic_cast<const List*>(input.data());

    // Start list
    output.push_back( Token(Token::eTYPE_LIST_START) );

    for(List::ObjectList::const_iterator iter=list->getValue().cbegin(); iter!=list->getValue().cend(); iter++){

        // Encode element
        if(!Codec::getEncoder()->encode(*iter, output)){
            return false;
        }
    }

    // End list
    output.push_back( Token(Token::eTYPE_ELEMENT_END) );

    return true;
}

} // be
