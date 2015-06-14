#include "bt/MetaInfo.h"
#include "bt/SingleFileInfo.h"
#include "bt/MultipleFileInfo.h"

#include <be/Codec.h>
#include <be/Dictionary.h>

#include <QCryptographicHash>
#include <QDebug>
#include <QUrl>

#define INFO_KEY "info"
#define ANNOUNCE_KEY "announce"
#define CREATION_DATE_KEY "creation date"
#define CREATED_BY_KEY  "created by"
#define ENCODING_KEY "encoding"
#define COMMENT_KEY "comment"

#define SCHEME_HTTP "http"
#define SCHEME_HTTPS "https"
#define SCHEME_UDP "udp"

namespace bt{

MetaInfo::MetaInfo(const QString& filePath) : mFilePath(filePath){
}

MetaInfo::MetaInfo(){
}

bool MetaInfo::load(){
    be::AObjectPtr result;

    if(!be::Codec::getDecoder()->decodeFile(mFilePath, &result)){
        qDebug() << "Erro decoding metainfo file";

        return false;
    }

    if(result->getType() != be::AObject::eTYPE_DICTIONARY){
        qDebug() << "Invalid master object type";
        return false;
    }

    QSharedPointer<be::Dictionary> masterDict = result.dynamicCast<be::Dictionary>();

    // Announce (mandatory)
    if(!masterDict->getString(ANNOUNCE_KEY, &mAnnounce)){
        qDebug() << ANNOUNCE_KEY " missing from dictionary";

        return false;
    }

    // Creation date (optional)
    qint32 creationDate = 0;
    if(masterDict->getInteger(CREATION_DATE_KEY, &creationDate)){
        mCreationDate = QDateTime::fromMSecsSinceEpoch(creationDate);
    }

    // Comment (optional)
    masterDict->getString(COMMENT_KEY, &mComment);

    // Author (optional)
    masterDict->getString(CREATED_BY_KEY, &mAuthor);

    // Encoding (optional)
    masterDict->getString(ENCODING_KEY, &mEncoding);

    QSharedPointer<be::Dictionary> infoDict;
    if(!masterDict->getDictionary(INFO_KEY, &infoDict)){
        qDebug() << INFO_KEY " missing from dictionary";

        return false;
    }

    Info::Mode mode = Info::detectMode(infoDict);

    if(mode == Info::eMODE_SINGLE_FILE){
        mInfo = new SingleFileInfo();
    }
    else if(mode == Info::eMODE_MULTIPLE_FILE){
        mInfo = new MultipleFileInfo();
    }
    else{
        return false;
    }

    mInfo->parse(infoDict);

    return true;
}

const Info* MetaInfo::getInfo() const{
    return mInfo;
}

const QString& MetaInfo::getAnnounce() const{
    return mAnnounce;
}

const QDateTime MetaInfo::getCreationDate() const{
    return mCreationDate;
}

const QString& MetaInfo::getComment() const{
    return mComment;
}

const QString& MetaInfo::getAuthor() const{
    return mAuthor;
}

const QString& MetaInfo::getEncoding() const{
    return mEncoding;
}

const QString& MetaInfo::getFilePath() const{
    return mFilePath;
}

MetaInfo::TrackerProtocol MetaInfo::getTrackerProtocol() const{
    QUrl url(mAnnounce);

    QString scheme = url.scheme();

    if(scheme.compare(SCHEME_HTTPS) == 0){
        return eTRACKER_HTTPS;
    }
    else if(scheme.compare(SCHEME_HTTP) == 0){
        return eTRACKER_HTTP;
    }
    else if(scheme.compare(SCHEME_UDP) == 0){
        return eTRACKER_UDP;
    }
    else{
        return eTRACKER_UNKOWN;
    }
}

} // bt

