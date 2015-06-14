#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <bt/TorrentManager.h>

namespace Ui
{
class MainWindow;
} // Ui

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

protected slots:
    void onPeerConnected(bt::PeerPtr peer);

    void onPeerDisconnected(bt::PeerPtr peer);

private:
    Ui::MainWindow *ui;
    bt::TorrentManager* mTorrentManager;
};

#endif // MAINWINDOW_H
