#include "be/Token.h"

namespace be{

Token::Token(TokenType type, const QByteArray& value) : mType(type), mValue(value){
}

Token::Token(TokenType type, const QString& value) : mType(type){
    mValue.append(value);
}

Token::Token(TokenType type) : mType(type){
}

Token::TokenType Token::getType() const{
    return mType;
}

const QByteArray& Token::getValue() const{
    return mValue;
}

} // be

QDebug operator<<(QDebug d, const be::Token& token){
    QString typeStr = "";

    switch(token.getType()){
        case be::Token::eTYPE_INVALID:
            typeStr = "INVALID";
            break;
        case be::Token::eTYPE_STRING:
            typeStr = "STRING";
            break;
        case be::Token::eTYPE_INTEGER:
            typeStr = "INTEGER";
            break;
        case be::Token::eTYPE_LIST_START:
            typeStr = "LIST_START";
            break;
        case be::Token::eTYPE_DICT_START:
            typeStr = "DICT_START";
            break;
        case be::Token::eTYPE_ELEMENT_END:
            typeStr = "ELEMENT_END";
            break;
        case be::Token::eTYPE_MAX:
            typeStr = "MAX";
            break;
    }

    d << "[" << typeStr << ":" << token.getValue() << "]";

    return d;
}

QDebug operator<<(QDebug d, QList<be::Token>& tokens){
    for(QList<be::Token>::iterator iter=tokens.begin(); iter!=tokens.end(); iter++){
        d << *iter;
    }

    return d;
}
