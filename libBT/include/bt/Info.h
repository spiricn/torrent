#ifndef INFO
#define INFO

#include <be/Dictionary.h>

#include "bt/Global.h"

namespace bt{

class BT_SHARED_EXPORT Info{
public:
    enum Mode{
        eMODE_INVALID,
        eMODE_SINGLE_FILE,
        eMODE_MULTIPLE_FILE,
        eMODE_MAX
    };

public:
    Info(Mode mode);

    virtual bool parse(be::DictionaryPtr infoDict);

    static Mode detectMode(be::DictionaryPtr infoDict);

    qint32 getPieceLength() const;

    const QList<QByteArray>& getPieces() const;

    bool isPrivate() const;

    Mode getMode() const;

    const QByteArray& getInfoHash() const;

private:
    be::DictionaryPtr mInfoDict;

    qint32 mPieceLength;

    QList<QByteArray> mPieces;

    qint32 mPrivate;

    Mode mMode;

    QByteArray mInfoHash;
};

} // bt

#endif // INFO

