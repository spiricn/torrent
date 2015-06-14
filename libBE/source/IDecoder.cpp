#include "be/IDecoder.h"

#include "be/Lexer.h"

#include <QBuffer>
#include <QDebug>

namespace be{

IDecoder::~IDecoder(){
}

bool IDecoder::decode(QIODevice *input, AObjectPtr* output){
    QList<Token> tokens;

    if(!Lexer::tokenize(input, tokens)){
        qDebug() << "Error tokenizing input";

        return false;
    }

    return decode(tokens, output);
}

bool IDecoder::decodeFile(const QString& filePath, AObjectPtr* output){
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Error openning file";

        return false;
    }

    bool res = decode(&file, output);

    file.close();

    return res;
}

bool IDecoder::decode(const QByteArray& byteArray, AObjectPtr* output){
    // Safe to const cast since we're openning it in ReadOnly mode
    QBuffer buffer(const_cast<QByteArray*>(&byteArray), NULL);

    if(!buffer.open(QIODevice::ReadOnly)){
        return false;
    }

    bool res = decode(&buffer, output);

    buffer.close();

    return res;
}

} // be


