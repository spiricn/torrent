#include "be/Lexer.h"

#include <QDebug>
#include <QByteArray>

#define DICTIONARY_START 'd'
#define LIST_START 'l'
#define INTEGER_START 'i'
#define ELEMENT_END 'e'
#define STRING_LENGTH_VALUE_SEPARATOR ':'
#define BENCODE_NUMBER_BASE ( 10 )

namespace be{

bool Lexer::tokenize(QIODevice* input, QList<Token>& output){
    while(!input->atEnd()){
        char probe;

        if(input->read(&probe, 1) != 1){
            qDebug() << "Error reading from input";

            return false;
        }

        if(probe == DICTIONARY_START){
            // Dictionary
            output.push_back( Token(Token::eTYPE_DICT_START) );
        }
        else if(probe == LIST_START){
            // List
            output.push_back( Token(Token::eTYPE_LIST_START) );
        }
        else if(probe == INTEGER_START){
            QString value = "";

            while(!input->atEnd()){
                char c = 0;

                if(input->read(&c, 1) != 1){
                    qDebug() << "Error reading from input";

                    return false;
                }

                if(c == 'e'){
                    break;
                }
                else{
                    value.append(c);
                }
            }

            output.push_back( Token(Token::eTYPE_INTEGER_START, value) );

            output.push_back( Token(Token::eTYPE_INTEGER, value) );

            output.push_back( Token(Token::eTYPE_ELEMENT_END, value) );
        }
        else if(probe == ELEMENT_END){
            // Element end
            output.push_back( Token(Token::eTYPE_ELEMENT_END) );
        }
        else if(QChar(probe).isDigit()){
            QString lengthStr = "";

            lengthStr.append(probe);

            bool readLength = false;

            while(!input->atEnd()){
                char c = 0;

                if(input->read(&c, 1) != 1){
                    qDebug() << "Error reading from input";

                    return false;
                }

                if(c == STRING_LENGTH_VALUE_SEPARATOR){
                    readLength = true;

                    break;
                }
                else{
                    lengthStr.append(c);
                }
            }

            if(!readLength){
                qDebug() << "Error reading string info";
                return false;
            }

            int length = lengthStr.toInt();

            QByteArray string = input->read(length);

            output.push_back(  Token(Token::eTYPE_STRING, string) );
        }
        else{
            qDebug() << "Unrecognized character " << probe;

            return false;
        }
    }

    return true;
}

bool Lexer::detokenize(const QList<Token>& input, QIODevice* output){
      for(QList<Token>::const_iterator iter=input.cbegin(); iter!=input.cend(); iter++){
        const Token token = *iter;

        switch(token.getType()){
            case Token::eTYPE_STRING: {
                // Write string length
                QByteArray stringLength;
                stringLength.append(QString::number(token.getValue().length(), BENCODE_NUMBER_BASE));

                if(output->write((stringLength)) != stringLength.length()){
                    return false;
                }

                // Write separator
                if(!output->putChar( STRING_LENGTH_VALUE_SEPARATOR )){
                    return false;
                }

                // Write string
                if(!output->write( token.getValue() )){
                    return false;
                }

                break;
            }

            case Token::eTYPE_INTEGER:
                // Integer value
                if(output->write(token.getValue()) != token.getValue().length()){
                    return false;
                }

                break;

            case Token::eTYPE_INTEGER_START:
                // Start integer object
                if(!output->putChar( INTEGER_START )){
                    return false;
                }

                break;

            case Token::eTYPE_LIST_START:
                if(!output->putChar( LIST_START )){
                    return false;
                }

                break;

            case Token::eTYPE_DICT_START:
                if(!output->putChar( DICTIONARY_START )){
                    return false;
                }
                break;

            case Token::eTYPE_ELEMENT_END:
                if(!output->putChar( ELEMENT_END )){
                    return false;
                }
                break;

            default:
                qDebug() << "Unrecognized token " << token.getType();

                return false;
        }
    }

    return true;
}

} // be



