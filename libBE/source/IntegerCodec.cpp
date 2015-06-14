#include "be/priv/IntegerCodec.h"

#include "be/Integer.h"

#include <qlist.h>

namespace be{

bool IntegerCodec::decode(QList<Token>& tokens, AObjectPtr* output){
    // Need at least 3 tokens to decode an integer (start, value and end)
    if(tokens.size() < 3){
        qDebug() << "Not enough tokens to decode integer";
        return false;
    }

    // Consume start
    if(tokens[0].getType() != Token::eTYPE_INTEGER_START){
        qDebug() << "Invalid token while parsing integer";
        return false;
    }
    tokens.pop_front();


    // Consume value
    if(tokens[0].getType() != Token::eTYPE_INTEGER){
        qDebug() << "Invalid token while parsing integer";
        return false;
    }

    Integer* obj = new Integer(tokens[0].getValue().toInt());
    tokens.pop_front();

    // Consume end
    if(tokens[0].getType() != Token::eTYPE_ELEMENT_END){
        qDebug() << "Invalid token while parsing integer";
        return false;
    }
    tokens.pop_front();

    *output = AObjectPtr(obj);

    return true;
}

bool IntegerCodec::encode(const AConstObjectPtr input, QList<Token>& output){
    const Integer* obj = dynamic_cast<const Integer*>(input.data());

    output.push_back( Token(Token::eTYPE_INTEGER_START) );

    output.push_back( Token(Token::eTYPE_INTEGER, QString::number(obj->getValue())) );

    output.push_back( Token(Token::eTYPE_ELEMENT_END) );

    return true;
}

} // be
