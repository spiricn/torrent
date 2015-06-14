#ifndef METAINFO
#define METAINFO

#include "bt/Info.h"

#include "bt/Global.h"

#include <QString>
#include <QDateTime>

namespace bt{

class BT_SHARED_EXPORT MetaInfo{
public:

    enum TrackerProtocol{
        eTRACKER_UNKOWN,
        eTRACKER_HTTP,
        eTRACKER_HTTPS,
        eTRACKER_UDP,
        eTRACKER_MAX
    };

public:
    MetaInfo(const QString& filePath);

    MetaInfo();

    bool load();

    const QString& getAnnounce() const;

    const QDateTime getCreationDate() const;

    const QString& getComment() const;

    const QString& getAuthor() const;

    const QString& getEncoding() const;

    const Info* getInfo() const;

    const QString& getFilePath() const;

    TrackerProtocol getTrackerProtocol() const;

private:
    QString mFilePath;

    QString mAnnounce;
    QDateTime mCreationDate;
    QString mComment;
    QString mAuthor;
    QString mEncoding;
    Info* mInfo;
};

} // bt

#endif // METAINFO

