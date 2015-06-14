#include "be/IEncoder.h"

#include "be/Lexer.h"

#include <QFile>
#include <QBuffer>
#include <QDebug>

namespace be{

IEncoder::~IEncoder(){
}

bool IEncoder::encodeFile(const AConstObjectPtr input, const QString& outputFilePath){
    QFile file(outputFilePath);

    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "Error openning file";

        return false;
    }

    bool res = encode(input, &file);

    file.close();

    return res;
}

bool IEncoder::encode(AConstObjectPtr input, QByteArray* output){
    QBuffer buffer(output);

    if(!buffer.open(QIODevice::WriteOnly)){
        qDebug() << "Error openning buffer for writing";

        return false;
    }

    bool res = encode(input, &buffer);

    buffer.close();

    return res;
}

bool IEncoder::encode(const AConstObjectPtr input, QIODevice* output){
    QList<Token> tokens;

    bool res = encode(input, tokens);

    if(!res){
        return false;
    }

    res = Lexer::detokenize(tokens, output);

    if(!res){
        qDebug() << "Error detokenizing";

        return false;
    }

    return res;
}

} // be

