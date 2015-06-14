#include "bt/SingleFileInfo.h"

#include <QDebug>

#define KEY_NAME "name"
#define KEY_LENGTH "length"
#define KEY_MD5SUM "md5sum"

namespace bt{

SingleFileInfo::SingleFileInfo() : Info(eMODE_SINGLE_FILE){
}

bool SingleFileInfo::parse(be::DictionaryPtr infoDict){
    if(!Info::parse(infoDict)){
        return false;
    }

    // Name (mandatory)
    if(!infoDict->getString(KEY_NAME, &mName)){
        qDebug() << KEY_NAME " field missing from info section";

        return false;
    }

    // Length (mandatory)
    if(!infoDict->getInteger(KEY_LENGTH, &mLength)){
        qDebug() << KEY_LENGTH " field missing from info section";

        return false;
    }

    // MD5Sum (optional)
    infoDict->getString(KEY_MD5SUM, &mMD5Sum);

    return true;
}

const QString& SingleFileInfo::getName() const{
    return mName;
}

qint32 SingleFileInfo::getLength() const{
    return mLength;
}

const QString& SingleFileInfo::getMD5Sum() const{
    return mMD5Sum;

}

} // bt
