#include "be/Codec.h"
#include "bt/Info.h"

#include <QDebug>
#include <QBuffer>
#include <QCryptographicHash>

#define PIECE_LENGTH_KEY "piece length"
#define PIECES_KEY "pieces"
#define PRIVATE_KEY "private"
#define LENGTH_KEY "length"
#define FILES_KEY "files"
#define PIECE_HASH_SIZE_B 20

namespace bt{

Info::Info(Mode mode) : mMode(mode), mPrivate(0){
}

bool Info::parse(be::DictionaryPtr infoDict){
    // Piece length (mandatory)

    if(!infoDict->getInteger(PIECE_LENGTH_KEY, &mPieceLength)){
        qDebug() << "Mandatory field " PIECE_LENGTH_KEY " missing from info section";

        return false;
    }

    // Pieces (mandatory)
    QByteArray pieces;
    if(!infoDict->getString(PIECES_KEY, &pieces)){
        qDebug() << "Mandatory field " PIECES_KEY " missing from info section";

        return false;
    }

    if(pieces.size() % PIECE_HASH_SIZE_B != 0){
        qDebug() << PIECES_KEY " field malformed";

        return false;
    }

    while(pieces.size() != 0){
        mPieces.push_back(pieces.mid(0, PIECE_HASH_SIZE_B));

        pieces.remove(0, PIECE_HASH_SIZE_B);
    }

    // Private (optional)
    infoDict->getInteger(PRIVATE_KEY, &mPrivate);


    QByteArray infoBytes;

    if(!be::Codec::getEncoder()->encode(infoDict, &infoBytes)){
        qDebug() << "Erro re-encoding info dictionary";

        return false;
    }

    mInfoHash = QCryptographicHash::hash(infoBytes, QCryptographicHash::Sha1);

    return true;
}

Info::Mode Info::detectMode(be::DictionaryPtr infoDict){
    // Detect mode
    if(infoDict->contains(FILES_KEY)){
        return eMODE_MULTIPLE_FILE;
    }
    else if(infoDict->contains(LENGTH_KEY)){
        return eMODE_SINGLE_FILE;
    }
    else{
        return eMODE_INVALID;
    }
}

qint32 Info::getPieceLength() const{
    return mPieceLength;
}

const QList<QByteArray>& Info::getPieces() const{
    return mPieces;
}

bool Info::isPrivate() const{
    return mPrivate == 1;
}

Info::Mode Info::getMode() const{
    return mMode;
}

const QByteArray& Info::getInfoHash() const{
    return mInfoHash;
}

} // bt


