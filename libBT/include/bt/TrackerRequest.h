#ifndef TRACKERREQUEST
#define TRACKERREQUEST


#include "bt/Global.h"

#include "bt/MetaInfo.h"

#include <QtNetwork/QNetworkRequest>

namespace bt{

class BT_SHARED_EXPORT TrackerRequest{
public:
    static QNetworkRequest build(const MetaInfo& meta, const QByteArray& peerId);
};

} // bt

#endif // TRACKERREQUEST

