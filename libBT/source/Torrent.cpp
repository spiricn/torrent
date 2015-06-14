#include "bt/Torrent.h"
#include "bt/MultipleFileInfo.h"
#include "bt/Utils.h"
#include "bt/PeerCommunication.h"

#include <QDir>

namespace bt{

Torrent::Torrent(ITorrentManager* parent, const QString& torrentFilePath, const QString& downloadDirectory) : mTorrentFilePath(torrentFilePath),
            mDownloadDirectory(downloadDirectory), mMeta(torrentFilePath), mParent(parent), mFirstResponseReceived(false) {
}

const MetaInfo& Torrent::getMeta() const{
    return mMeta;
}

bool Torrent::start(){
    if(!mMeta.load()){
        qDebug() << "Error loading meta file";


        return false;
    }

    mTracker = new Tracker(&mMeta, mParent->getPeerId());

    connect(mTracker, SIGNAL(onTrackerResponse(const TrackerResponse&)), this, SLOT(onTrackerResponse(const TrackerResponse&)));


    const bt::MultipleFileInfo* info = dynamic_cast<const bt::MultipleFileInfo*>(mMeta.getInfo());

    // Create empty files
    QDir downloadDir(mDownloadDirectory);

    for(QList<bt::MultipleFileInfo::FileEntry>::const_iterator iter=info->getFiles().cbegin(); iter!=info->getFiles().cend(); iter++){
        QString filePath = downloadDir.filePath((*iter).path);

        bt::createFile(filePath, (*iter).length, false /* don't overwrite if file already exists */);
    }

    // Send initial request
    return mTracker->sendRequest();
}

void Torrent::onRequestTimer(){
    mTracker->sendRequest();
}

PeerPtr Torrent::findPeer(Peer::Id id){
    for(PeerMap::iterator iter=mPeers.begin(); iter!=mPeers.end(); iter++){
        if((*iter)->getId() == id){
            return *iter;
        }
    }

    return PeerPtr(NULL);
}

void Torrent::onTrackerResponse(const TrackerResponse& response){
    if(!mFirstResponseReceived){
        // First response
        mFirstResponseReceived = true;
    }

    mLastResponse = response;

    for(QList<Peer>::const_iterator iter=response.getPeers().cbegin(); iter!=response.getPeers().cend(); iter++){
        PeerPtr peer = findPeer((*iter).getId());

        if(peer == NULL){
            if((*iter).getIP() == bt::getLocalAddress()){
                // Don't add our selves as a peer
                continue;
            }

            addPeer((*iter));
        }
    }

    for(PeerMap::iterator i=mPeers.begin(); i!=mPeers.end(); i++){
        bool clientConnected = false;

        // Check if this peer is in the list of peers from the tracker response
        for(QList<Peer>::const_iterator j=response.getPeers().cbegin(); j!=response.getPeers().cend(); j++){
            if((*i)->getId() == (*j).getId()){
                clientConnected = true;
                break;
            }
        }

        if(!clientConnected){
            // Peer no longer in list of peers
            deletePeer((*i)->getId());
        }
    }

    //  TODO: Using hard coded interval value for now
    const int debugInterval = 3000;

    QTimer::singleShot(debugInterval, this, SLOT(onRequestTimer()));
}

void Torrent::addPeer(const Peer& peer){
    qDebug() << "Adding peer: " << peer.getId();

    PeerPtr newPeer = PeerPtr(new Peer(peer));

    mPeers.insert(peer.getId(), newPeer);

    PeerCommunication* conn = new PeerCommunication(mParent, newPeer, mMeta);

    emit onPeerConnected(newPeer);
}

void Torrent::deletePeer(Peer::Id id){
    qDebug() << "Removing peer: " << id;

    PeerPtr peerPtr = findPeer(id);

    mPeers.remove(id);

    emit onPeerDisconnected(peerPtr);
}

} //bt
