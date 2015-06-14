#ifndef ITORRENTMANAGER
#define ITORRENTMANAGER

#include <QByteArray>

namespace bt{

class ITorrentManager{
public:
    virtual const QByteArray& getPeerId() const = 0;
};

} // bt
#endif // ITORRENTMANAGER

