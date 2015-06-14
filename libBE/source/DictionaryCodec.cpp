#include "be/priv/DictionaryCodec.h"

#include "be/Dictionary.h"

#include "be/Codec.h"

namespace be{

bool DictionaryCodec::decode(QList<Token>& tokens, AObjectPtr* output){
    Dictionary* obj = new Dictionary();

    // Sanity check
    Q_ASSERT(!tokens.empty() && tokens[0].getType() == Token::eTYPE_DICT_START);

    // Consume dictionary start token
    tokens.pop_front();

    while(true){
        if(tokens.empty()){
            qDebug() << "Ran out of tokens while parsing dictionary";
            return false;
        }

        if(tokens[0].getType() == Token::eTYPE_ELEMENT_END){
            // Dictionary done
            tokens.pop_front();
            break;
        }

        AObjectPtr dictKey;

        // Decode key object
        if(!Codec::getDecoder()->decode(tokens, &dictKey)){
            // Error decoding key
            qDebug() << "Error decoding dictionary key";
            return false;
        }

        // Keys may only be strings
        if(dictKey->getType() != AObject::eTYPE_STRING){
            qDebug() << "Invalid dictionary key type";
            return false;
        }

        // Decode value object
        AObjectPtr dictValue;

        if(!Codec::getDecoder()->decode(tokens, &dictValue)){
            // Error decoding value
            qDebug() << "Error decoding dictionary value";
            return false;
        }

        // Add them to our map
        obj->getValue().insert(dictKey.dynamicCast<String>(), dictValue);
    }

    *output = AObjectPtr(obj);

    return true;

}

bool compareKeys(StringPtr keyA, StringPtr keyB){
    return keyA->getValue() < keyB->getValue();
}

bool DictionaryCodec::encode(const AConstObjectPtr input, QList<Token>& output){
    const Dictionary* dict = dynamic_cast<const Dictionary*>(input.data());

    // Dictionary start
    output.push_back(Token::eTYPE_DICT_START);

    // Keys need to be sorted
    QList<StringPtr> keys = dict->getValue().keys();
    qSort(keys.begin(), keys.end(), compareKeys);

    for(QList<StringPtr>::iterator iter=keys.begin(); iter!=keys.end(); iter++){
        StringPtr key = *iter;

        AObjectPtr value = dict->getValue()[key];

        // Encode key
        if(!Codec::getEncoder()->encode(key, output)){
            qDebug() << "Error encoding dictionary key";

            return false;
        }

        // Encode value
        if(!Codec::getEncoder()->encode(value, output)){
            qDebug() << "Error encoding dictionary value";

            return false;
        }
    }

    // Dictionary end
    output.push_back(Token::eTYPE_ELEMENT_END);

    return true;
}

} // be
