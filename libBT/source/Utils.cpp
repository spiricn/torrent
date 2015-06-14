#include "bt/Utils.h"
#include "bt/ExternalIPChecker.h"

#include <QString>
#include <QHostInfo>
#include <QFile>

#define FILE_CREATE_CHUNK_SIZE ( 1024 )

namespace bt{

QByteArray generatePeerId(char clientId[2], int versionNumber){
    QByteArray res;

    // 1 Byte
    res.append('-');

    // 2 Bytes
    res.append(clientId);

    // 4 Bytes
    res.append( QString::number(versionNumber).rightJustified(4, '0') );

    // 1 Byte
    res.append('-');

    // 12 Bytes
    for(int i=0; i<12; i++){
        res.append((char)(qrand() % 255));
    }

    // Sanity check
    Q_ASSERT(res.size() == 20);

    return res;
}

bool createFile(const QString& filePath, quint32 fileSize, bool overwrite){
    QFile file(filePath);

    if(file.exists() && !overwrite){
        return false;
    }

    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    // Use heap instead of stack
    char* chunk = new char[FILE_CREATE_CHUNK_SIZE];
    memset(chunk, 0x00, FILE_CREATE_CHUNK_SIZE);


    quint32 remainingBytes = fileSize;

    while(remainingBytes){
        quint32 numBytes = remainingBytes >= FILE_CREATE_CHUNK_SIZE ? FILE_CREATE_CHUNK_SIZE : remainingBytes;

        quint64 bytesWritten = file.write(chunk, numBytes);

        if(bytesWritten < 0){
            file.close();

            return false;
        }

        remainingBytes -=  bytesWritten;
    }

    file.close();

    delete[] chunk;

    return true;
}

const QHostAddress& getLocalAddress(){
    return ExternalIPChecker::getAddress();
}

} // bt

