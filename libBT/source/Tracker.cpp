#include "bt/Tracker.h"

namespace bt{

Tracker::Tracker(MetaInfo* meta, const QByteArray& peerId) : mMeta(meta){
    QObject::connect(&mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

    mPeerId = peerId;
}

bool Tracker::sendRequest(){
    QNetworkRequest request = TrackerRequest::build(*mMeta, mPeerId);

    // Support only HTTP & HTTPS for now
    if(mMeta->getTrackerProtocol() != MetaInfo::eTRACKER_HTTP && mMeta->getTrackerProtocol() != MetaInfo::eTRACKER_HTTPS){
        qDebug() << "Unsupported announce protocol " << mMeta->getTrackerProtocol();

        return false;
    }

    mReply = mManager.get(request);

    return true;
}

void Tracker::requestFinished(QNetworkReply* reply){
    QByteArray replyBytes = reply->readAll();

    be::AObjectPtr replyDict;

    if(!be::Codec::getDecoder()->decode(replyBytes, &replyDict)){
        qDebug() << "Error decoding response";
        return;
    }

    QSharedPointer<be::Dictionary> masterDict = replyDict.dynamicCast<be::Dictionary>();

    TrackerResponse response(masterDict);

    if(!response.parse()){
        qDebug() << "Error parsing response";
        return;
    }

    if(response.isFailed()){
        qDebug() << "Request failed: " << response.getFailureReason();
    }
    else{
        emit onTrackerResponse(response);
    }
}

} // bt


