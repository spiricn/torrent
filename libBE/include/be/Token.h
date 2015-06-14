#ifndef TOKEN
#define TOKEN

#include "be/Global.h"

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace be{

class BE_SHARED_EXPORT Token{
public:
    enum TokenType{
        eTYPE_INVALID,
        eTYPE_STRING,
        eTYPE_INTEGER_START,
        eTYPE_INTEGER,
        eTYPE_LIST_START,
        eTYPE_DICT_START,
        eTYPE_ELEMENT_END,
        eTYPE_MAX
    };

public:
    Token(TokenType type, const QByteArray& value);

    Token(TokenType type, const QString& value);

    Token(TokenType type);

    TokenType getType() const;

    const QByteArray& getValue() const;

private:
    TokenType mType;
    QByteArray mValue;
};

} // be

QDebug operator<<(QDebug d, const be::Token& token);

QDebug operator<<(QDebug d, QList<be::Token>& tokens);

#endif // TOKEN

