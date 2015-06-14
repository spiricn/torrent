#ifndef MANAGER
#define MANAGER

#include "be/Codec.h"

#include "bt/MetaInfo.h"
#include "bt/TrackerRequest.h"
#include "bt/TrackerResponse.h"
#include "bt/Global.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply.h>
#include <QUrlQuery>

namespace bt{

class BT_SHARED_EXPORT Tracker : public QObject{
public:
    Q_OBJECT

public:
    Tracker(MetaInfo* meta, const QByteArray& peerId);

    bool sendRequest();

protected slots:
    void requestFinished(QNetworkReply* reply);

signals:
    void onTrackerResponse(const TrackerResponse& response);

private:
    MetaInfo* mMeta;
    QNetworkAccessManager mManager;
    QNetworkReply* mReply;
    QByteArray mPeerId;
};

} // bt

#endif // MANAGER

