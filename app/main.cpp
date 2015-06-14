#include "MainWindow.h"
#include <QApplication>

#include <QDebug>

#if 0

#include "be/Codec.h"
#include "bt/Tracker.h"

int main(){
    be::AObjectPtr obj;

    if(!be::Codec::getDecoder()->decodeFile(QString("d:/home/dev/workspace/torrent/app/test.torrent"), &obj)){
        qDebug() << "Error decoding";
        return 1;
    }

    if(!be::Codec::getEncoder()->encodeFile(obj, QString("C:/users/nikola/desktop/renc.torrent"))){
        qDebug() << "Error encoding";
        return 1;
    }

    qDebug() << "OK";

    return 0;
}

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
#endif
