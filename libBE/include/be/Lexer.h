#ifndef TOKENIZER
#define TOKENIZER

#include "be/Token.h"
#include "be/Global.h"

#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QDebug>

namespace be{

class BE_SHARED_EXPORT Lexer{
public:
    static bool tokenize(QIODevice* input, QList<Token>& output);

    static bool detokenize(const QList<Token>& input, QIODevice* output);
};

} //be

#endif // TOKENIZER

