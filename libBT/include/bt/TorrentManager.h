#ifndef TORRENTMANAGER
#define TORRENTMANAGER

#include "bt/Global.h"

#include "bt/Torrent.h"
#include "bt/ITorrentManager.h"

namespace bt{

class BT_SHARED_EXPORT TorrentManager : public ITorrentManager{
public:
    TorrentManager(const QByteArray& peerId);

    TorrentPtr addTorrent(const QString& metaInfoFilePath, const QString& downloadDirectory);

    const QByteArray& getPeerId() const;

private:
    QList<TorrentPtr> mTorrents;
    QByteArray mPeerId;
};

} // bt

#endif // TORRENTMANAGER

