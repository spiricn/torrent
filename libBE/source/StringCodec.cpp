#include "be/priv/StringCodec.h"

#include "be/String.h"

namespace be{

bool StringCodec::decode(QList<Token>& tokens, AObjectPtr* output){
    // Sanity check
    Q_ASSERT(!tokens.empty() && tokens[0].getType() == Token::eTYPE_STRING);

    StringPtr obj(new String(tokens[0].getValue()));

    tokens.pop_front();

    *output = obj;

    return true;
}

bool StringCodec::encode(const AConstObjectPtr input, QList<Token>& output){
    const String* string = dynamic_cast<const String*>(input.data());

    output.push_back(Token(Token::eTYPE_STRING, string->getValue()));

    return true;
}

} // be
