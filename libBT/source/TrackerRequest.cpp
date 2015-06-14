#include "bt/TrackerRequest.h"

#define INFO_HASH_KEY "info_hash"
#define PEER_ID_KEY "peer_id"
#define PORT_KEY "port"
#define UPLOADED_KEY "uploaded"
#define DOWNLOADED_KEY "downloaded"
#define LEFT_KEY "left"
#define COMPACT_KEY "compact"
#define NO_PEER_ID_KEY "no_peer_id"


#include <QUrl>
#include <QUrlQuery>

namespace bt{

QNetworkRequest TrackerRequest::build(const MetaInfo& meta, const QByteArray& peerId){
    QNetworkRequest request;

    // Chcek if announce URL has a query in it
    QString announceQuery = "";

    QString urlStr = meta.getAnnounce();

    int announceQueryStart = meta.getAnnounce().indexOf("?");

    if(announceQueryStart > 0){
        announceQuery = meta.getAnnounce().mid(announceQueryStart + 1, meta.getAnnounce().length());

        urlStr = urlStr.mid(0, announceQueryStart);
    }

    QUrl url = QUrl(urlStr);

    // Use announce query as base
    QUrlQuery query(announceQuery);

    query.addQueryItem(INFO_HASH_KEY, meta.getInfo()->getInfoHash().toPercentEncoding());

    query.addQueryItem(PEER_ID_KEY, peerId.toPercentEncoding());

    // TODO
    query.addQueryItem(PORT_KEY, "13099");

    // TODO
    query.addQueryItem(UPLOADED_KEY, "0");

    // TODO
    query.addQueryItem(DOWNLOADED_KEY, "0");

    // TODO
    query.addQueryItem(LEFT_KEY, "100");

    // TODO
    query.addQueryItem(COMPACT_KEY, "0");

    // TODO
    query.addQueryItem(NO_PEER_ID_KEY, "0");

    url.setQuery(query);

    request.setUrl( url );

    return request;
}

} // bt
