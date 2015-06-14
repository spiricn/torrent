#include "bt/TrackerResponse.h"

#include <be/Dictionary.h>

#define FAILURE_REASON_KEY "failure reason"
#define WARNING_MESSAGE_KEY "warning message"
#define INTERVAL_KEY "interval"
#define MIN_INTERVAL_KEY "min interval"
#define TRACKER_ID_KEY "tracker id"
#define COMPLETE_KEY "complete"
#define INCOMPLETE_KEY "incomplete"
#define PEERS_KEY "peers"
#define BYTES_PER_PEER ( 6 )

namespace bt{

TrackerResponse::TrackerResponse(be::DictionaryPtr dict) : mDict(dict), mMinInterval(-1){
}

TrackerResponse::TrackerResponse(){
}

bool TrackerResponse::parse(){
    // Failure reason (optional)
    if(mDict->getString(FAILURE_REASON_KEY, &mFailureReason)){
        // No other keys are presetn if this one is
        return true;
    }

    // Warning (optional)
    mDict->getString(WARNING_MESSAGE_KEY, &mWarningMessage);

    // Interval (mandatory)
    if(!mDict->getInteger(INTERVAL_KEY, &mInterval)){
        qDebug() << INTERVAL_KEY " missing from server response";

        return false;
    }

    // Min interval (optional)
    mDict->getInteger(MIN_INTERVAL_KEY, &mMinInterval);

    // Tracker ID (optional)
    mDict->getString(TRACKER_ID_KEY, &mTrackerId);

    // Seeders (mandatory)
    if(!mDict->getInteger(COMPLETE_KEY, &mComplete)){
        qDebug() << COMPLETE_KEY " missing from server response";

        return false;
    }

    // Leechers (mandatory)
    if(!mDict->getInteger(INCOMPLETE_KEY, &mIncomplete)){
        qDebug() << INCOMPLETE_KEY " missing from server response";

        return false;
    }


    QList<be::AObjectPtr>* peersList;

    if(mDict->getList(PEERS_KEY, &peersList)){
        // Dictionary model
        for(be::List::ObjectList::iterator iter=peersList->begin(); iter!=peersList->end(); iter++){
            be::DictionaryPtr peerDict = (*iter).dynamicCast<be::Dictionary>();

            Peer peer(peerDict);

            if(!peer.parse()){
                qDebug() << "Error pasring peer info";

                return false;
            }

            mPeers.push_back(peer);
        }
    }

    QByteArray peersBytes;
    if(mDict->getString(PEERS_KEY, &peersBytes)){
        // Binary model
        if(peersBytes.size() % BYTES_PER_PEER != 0){
            qDebug() << "Malformed peers binary info";
            return false;
        }

        while(peersBytes.size() > 0){
            QByteArray peerInfo = peersBytes.mid(0, BYTES_PER_PEER);

            peersBytes.remove(0, BYTES_PER_PEER);

            Peer peer(peerInfo);

            if(!peer.parse()){
                qDebug() << "Error pasring peer info";

                return false;
            }

            mPeers.push_back(peer);
        }
    }
    else{
        // Neither, or missing
        qDebug() << PEERS_KEY " missing from server response";
        return false;
    }
    return true;
}

bool TrackerResponse::isFailed() const{
    return mFailureReason.size() > 0;
}

const QString& TrackerResponse::getFailureReason() const{
    return mFailureReason;
}


const QString& TrackerResponse::getWarningMessage() const{
    return mWarningMessage;
}

qint32 TrackerResponse::getInterval() const{
    return mInterval;
}

qint32 TrackerResponse::getMinInterval() const{
    return mMinInterval;
}


const QString& TrackerResponse::getTrackerId() const{
    return mTrackerId;
}

qint32 TrackerResponse:: getComplete() const{
    return mComplete;
}


qint32 TrackerResponse::getIncomplete() const{
    return mIncomplete;
}

const QList<Peer>& TrackerResponse::getPeers() const{
    return mPeers;
}

} // bt
