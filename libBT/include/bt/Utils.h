#ifndef UTILS
#define UTILS

#include "bt/Global.h"

#include <QByteArray>
#include <QHostAddress>

namespace bt{
/*
 * Generates 20-bytes peer ID using azureus-style:
 *  '-', two characters for client id, four ascii digits for version number, '-', followed by random numbers.
 */
QByteArray BT_SHARED_EXPORT generatePeerId(char clientId[2], int versionNumber);

bool createFile(const QString& filePath, quint32 fileSize, bool overwrite);

const QHostAddress& getLocalAddress();

} // bt

#endif // UTILS

