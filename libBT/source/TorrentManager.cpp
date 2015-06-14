#include "bt/TorrentManager.h"
#include "bt/ExternalIPChecker.h"
#include "bt/Utils.h"

#include <QHostInfo>
#include <QCoreApplication>

namespace bt{

TorrentManager::TorrentManager(const QByteArray &peerId) : mPeerId(peerId){
    // Wait untill our address becomes available (might use up too much CPU)
    while(bt::getLocalAddress().toIPv4Address() == 0){
        QCoreApplication::processEvents(0);
    }

}

TorrentPtr TorrentManager::addTorrent(const QString& metaInfoFilePath, const QString& downloadDirectory){
    TorrentPtr torrent = TorrentPtr(new Torrent(this, metaInfoFilePath, downloadDirectory));

    if(!torrent->start()){
        qDebug() << "Error starting torrent";

        return TorrentPtr();
    }

    mTorrents.push_back(torrent);

    return torrent;
}

const QByteArray& TorrentManager::getPeerId() const{
    return mPeerId;
}

} // bt
