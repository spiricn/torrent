#ifndef TORRENT_H
#define TORRENT_H

#include "bt/Global.h"

#include "bt/MetaInfo.h"
#include "bt/Tracker.h"
#include "bt/ITorrentManager.h"

#include <QSharedPointer>
#include <QTimer>

namespace bt{

class BT_SHARED_EXPORT Torrent : public QObject {
public:
    Q_OBJECT

public:
    const MetaInfo& getMeta() const;

private:
    Torrent(ITorrentManager* parent, const QString& torrentFilePath, const QString& downloadDirectory);

    bool start();

    PeerPtr findPeer(Peer::Id id);

    void addPeer(const Peer& peer);

    void deletePeer(Peer::Id id);

signals:
    void onPeerConnected(bt::PeerPtr peer);

    void onPeerDisconnected(bt::PeerPtr peer);

private slots:
    void onTrackerResponse(const TrackerResponse& response);

    void onRequestTimer();

private:
    typedef QMap<Peer::Id, PeerPtr> PeerMap;

private:
    MetaInfo mMeta;
    Tracker* mTracker;
    QString mTorrentFilePath;
    ITorrentManager* mParent;
    QTimer mRequestTimer;
    TrackerResponse mLastResponse;
    bool mFirstResponseReceived;
    PeerMap mPeers;
    QString mDownloadDirectory;

private:
    friend class TorrentManager;
};

typedef QSharedPointer<Torrent> TorrentPtr;

} // bt

#endif // TORRENT_H

