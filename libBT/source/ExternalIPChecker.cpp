#include "bt/ExternalIPChecker.h"

#include <QNetworkAccessManager>
#include <QSemaphore>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHostAddress>

#define IP_SERVER "http://ipv4bot.whatismyipaddress.com"
#define CHECKER_USER_AGENT "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.132 Safari/537.36"

namespace bt{

ExternalIPChecker* ExternalIPChecker::sInstance = NULL;

ExternalIPChecker* ExternalIPChecker::getInstance(){
    if(sInstance == NULL){
        sInstance = new ExternalIPChecker;
    }

    return sInstance;
}


const QHostAddress& ExternalIPChecker::getAddress(){
    return getInstance()->mAddress;
}

ExternalIPChecker::ExternalIPChecker(){
    connect(&mManager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(onReply(QNetworkReply*))
    );

    QNetworkRequest request(QUrl(IP_SERVER));

    // ipv4bot.whatismyipaddress requires user agent header to be set !
    request.setRawHeader("User-Agent", CHECKER_USER_AGENT);

    mManager.get(request);
}

void ExternalIPChecker::onReply(QNetworkReply* reply){
    if(reply->error() == QNetworkReply::NoError){
        mAddress = QHostAddress(QString(reply->readAll()));

        qDebug() << "Got external IP address: " << mAddress;
    }

    emit onAddressAcquired(mAddress);
}

} // bt
