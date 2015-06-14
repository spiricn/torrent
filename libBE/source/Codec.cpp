#include "be/Codec.h"

#include "be/AObject.h"

#include "be/priv/IntegerCodec.h"
#include "be/priv/ListCodec.h"
#include "be/priv/StringCodec.h"
#include "be/priv/DictionaryCodec.h"

#include <QFile>

namespace be{

Codec* Codec::sInstance = NULL;

Codec::Codec(){
    mCodecs[AObject::eTYPE_INTEGER] = QSharedPointer<ICodec>(new IntegerCodec);
    mCodecs[AObject::eTYPE_STRING] = QSharedPointer<ICodec>(new StringCodec);
    mCodecs[AObject::eTYPE_LIST] = QSharedPointer<ICodec>(new ListCodec);
    mCodecs[AObject::eTYPE_DICTIONARY] = QSharedPointer<ICodec>(new DictionaryCodec);
}

bool Codec::decode(QList<Token>& tokens, AObjectPtr* output){
    if(tokens.empty()){
        qDebug() << "Could not decode empty input";

        return false;
    }

    IDecoder* decoder = getInstance()->findDecoder(tokens);

    if(decoder == NULL){
        qDebug() << "Could not find decoder for token " << tokens[0].getType();

        return false;
    }

    return decoder->decode(tokens, output);
}

bool Codec::encode(const AConstObjectPtr input, QList<Token>& output){
    IEncoder* encoder = getInstance()->findEncoder(input);


    if(encoder == NULL){
        qDebug() << "Could not find encoder for token " << output[0].getType();

        return false;
    }

    return encoder->encode(input, output);
}

IEncoder* Codec::getEncoder(){
    return dynamic_cast<IEncoder*>(getInstance());
}


IDecoder* Codec::getDecoder(){
    return dynamic_cast<IDecoder*>(getInstance());
}

Codec* Codec::getInstance(){
    if(sInstance == NULL){
        sInstance = new Codec;
    }

    return sInstance;
}

IDecoder* Codec::findDecoder(const QList<Token>& tokens){
    if(tokens.empty()){
        return NULL;
    }

    switch(tokens[0].getType()){
        case Token::eTYPE_STRING:
            return dynamic_cast<IDecoder*>(mCodecs[AObject::eTYPE_STRING].data());

        case Token::eTYPE_INTEGER_START:
            return dynamic_cast<IDecoder*>(mCodecs[AObject::eTYPE_INTEGER].data());

        case Token::eTYPE_LIST_START:
            return dynamic_cast<IDecoder*>(mCodecs[AObject::eTYPE_LIST].data());

        case Token::eTYPE_DICT_START:
            return dynamic_cast<IDecoder*>(mCodecs[AObject::eTYPE_DICTIONARY].data());

        default:
            return NULL;
    }
}

IEncoder* Codec::findEncoder(const AConstObjectPtr obj){
    return dynamic_cast<IEncoder*>(mCodecs[obj->getType()].data());
}

} // be
