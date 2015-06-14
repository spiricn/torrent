#include "bt/MultipleFileInfo.h"

#include <QDebug>
#include <QDir>

#define NAME_KEY "name"
#define FILES_KEY "files"
#define LENGTH_KEY "length"
#define MD5SUM_KEY "md5sum"
#define PATH_KEY "path"

namespace bt{

MultipleFileInfo::MultipleFileInfo() : Info(eMODE_MULTIPLE_FILE){
}

bool MultipleFileInfo::parse(be::DictionaryPtr infoDict){
    if(!Info::parse(infoDict)){
        return false;
    }

    // Name (mandatory)
    if(!infoDict->getString(NAME_KEY, &mName)){
        qDebug() << NAME_KEY " key missing from info section";

        return false;
    }


    // List of dictionaries, one for each file (mandatory)
    be::List::ObjectList* files = NULL;

    if(!infoDict->getList(FILES_KEY, &files)){
        qDebug() << FILES_KEY " key missing from info section";

        return false;
    }

    for(be::List::ObjectList::iterator iter=files->begin(); iter!=files->end(); iter++){
        FileEntry entry;

        // File dictionary element
        be::AObjectPtr obj = *iter;

        if(obj->getType() != be::AObject::eTYPE_DICTIONARY){
            qDebug() << "Malformed " FILES_KEY " list in info section (" << obj->getType() << ")";

            return false;
        }

        be::DictionaryPtr dict = obj.dynamicCast<be::Dictionary>();

        // Length (mandatory)
        if(!dict->getInteger(LENGTH_KEY, &entry.length)){
            qDebug() << LENGTH_KEY " missing from file entry in info section";

            return false;
        }

        // MD5SUM (optional)
        dict->getString(MD5SUM_KEY, &entry.md5sum);

        // Path (mandatory)
        be::List::ObjectList* pathList = NULL;
        if(!dict->getList(PATH_KEY, &pathList)){
            qDebug() << PATH_KEY " missing from file entry in info section";

            return false;
        }

        for(be::List::ObjectList::iterator i=pathList->begin(); i!=pathList->end(); i++){
            be::AObjectPtr segmentObj = *i;

            if(segmentObj->getType() != be::AObject::eTYPE_STRING){
                qDebug() << "Malformed file path segment in info section";

                return false;
            }

            QString segment = segmentObj.dynamicCast<be::String>()->getValue();

            entry.path.append(segment + QDir::separator());
        }

        // Remove the last path separator
        entry.path.remove(entry.path.length() - 1, 1);

        mFiles.push_back(entry);
    }

    return true;
}

const QString& MultipleFileInfo::getName() const{
    return mName;
}

const QList<MultipleFileInfo::FileEntry>& MultipleFileInfo::getFiles() const{
    return mFiles;
}

} // bt
