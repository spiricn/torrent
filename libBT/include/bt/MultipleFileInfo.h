#ifndef MULTIPLEFILEINFO
#define MULTIPLEFILEINFO

#include "bt/Info.h"

#include "bt/Global.h"

namespace bt{

class BT_SHARED_EXPORT MultipleFileInfo : public Info{
public:
    struct FileEntry{
        qint32 length;
        QString md5sum;
        QString path;
    };

public:
    MultipleFileInfo();

    bool parse(be::DictionaryPtr infoDict);

    const QString& getName() const;

    const QList<FileEntry>& getFiles() const;

private:
    QString mName;
    QList<FileEntry> mFiles;
};

} // bt

#endif // MULTIPLEFILEINFO

