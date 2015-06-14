#ifndef SINGLEFILEINFO_H
#define SINGLEFILEINFO_H

#include "bt/Info.h"

#include "bt/Global.h"

namespace bt{

class BT_SHARED_EXPORT SingleFileInfo : public Info{
public:
    SingleFileInfo();

    bool parse(be::DictionaryPtr infoDict);

    const QString& getName() const;

    qint32 getLength() const;

    const QString& getMD5Sum() const;

private:
    QString mName;
    qint32 mLength;
    QString mMD5Sum;
}; // SingleFileInfo

} // bt

#endif // SINGLEFILEINFO_H

