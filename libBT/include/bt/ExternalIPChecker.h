#ifndef EXTERNALIPCHECKER
#define EXTERNALIPCHECKER

#include <QHostAddress>
#include <QNetworkAccessManager>

namespace bt{

class ExternalIPChecker : public QObject{
public:
    Q_OBJECT

public:
    static const QHostAddress& getAddress();

private:
    ExternalIPChecker();

    static ExternalIPChecker* getInstance();

signals:
    void onAddressAcquired(const QHostAddress& address);

private slots:
    void onReply(QNetworkReply* reply);

private:
    static ExternalIPChecker* sInstance;
    QNetworkAccessManager mManager;
    QHostAddress mAddress;
};

} // bt

#endif // EXTERNALIPCHECKER

