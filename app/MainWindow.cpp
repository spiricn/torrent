#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QTreeWidgetItemIterator>

#include <bt/MetaInfo.h>
#include <bt/Tracker.h>
#include <bt/Utils.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    mTorrentManager = new bt::TorrentManager(bt::generatePeerId("BT", 42));

    bt::TorrentPtr torrent = mTorrentManager->addTorrent("d:/home/dev/workspace/torrent/app/test.torrent", "C:/users/nikola/desktop");

    if(torrent == NULL){
        qDebug() << "Error adding torrent";

        return;
    }


    connect(torrent.data(), SIGNAL(onPeerConnected(bt::PeerPtr)), this, SLOT(onPeerConnected(bt::PeerPtr)));
    connect(torrent.data(), SIGNAL(onPeerDisconnected(bt::PeerPtr)), this, SLOT(onPeerConnected(bt::PeerPtr)));

    ui->widget->display(torrent->getMeta());
}

void MainWindow::onPeerConnected(bt::PeerPtr peer){
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->peerList);

    item->setText(0, peer->getIP().toString());
    item->setText(1, QString::number(peer->getPort()));
    item->setText(2, QString::number(peer->getId()));

    item->setData(0, Qt::UserRole, QVariant(peer->getId()));

    ui->peerList->addTopLevelItem(item);
}

void MainWindow::onPeerDisconnected(bt::PeerPtr peer){
   QTreeWidgetItemIterator iter(ui->peerList);


   while(*iter){
       QTreeWidgetItem* item = *iter;

       bt::Peer::Id id = item->data(0, Qt::UserRole).toLongLong();

       if(id == peer->getId()){
           delete item;
           break;
       }

       ++iter;
   }
}

MainWindow::~MainWindow(){
    delete ui;
}
