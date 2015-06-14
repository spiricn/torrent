#include "bt/pwp/RawMessage.h"

#include <QDebug>
#include <QtEndian>
#include <QBuffer>


#define MAX_PAYLOAD_CHUNK_SIZE ( 512 )

namespace bt{

RawMessage::RawMessage() : mId(eID_INVALID), mLengthPrefix(-1){
}

RawMessage::RawMessage(Id id) : mId(id) {
}

IRawMessage::DeserializationStatus RawMessage::deserialize(QIODevice* input){
    if(mLengthPrefix == -1){
        if(input->bytesAvailable() <  4){
            // Not enough bytes
            return eSTATUS_INCOMPLETE;
        }

        if(input->read(reinterpret_cast<char*>(&mLengthPrefix), sizeof(qint32)) != sizeof(qint32)){
            qDebug() << "Error reading message length";

            return eSTATUS_ERROR;
        }

        mLengthPrefix = qFromBigEndian<qint32>(reinterpret_cast<uchar*>(&mLengthPrefix));
    }

    if(mId == eID_INVALID){
        if(input->bytesAvailable() < 1){
            // Not enough bytes
            return eSTATUS_INCOMPLETE;
        }

        char cid;

        if(!input->getChar(&cid)){
            qDebug() << "Error reading message ID";

            return eSTATUS_ERROR;
        }

        if(cid <= eID_INVALID || cid >= eID_MAX){
            qDebug() << "message ID out of valid range: " << static_cast<quint8>(cid);

            return eSTATUS_ERROR;
        }

        mId = static_cast<Id>(cid);
    }

    qint32 totalPayloadSize = mLengthPrefix - 1;

    qint32 bytesRemaining = totalPayloadSize - mPayload.size();

    if(bytesRemaining > 0){
        qint32 chunkSize = bytesRemaining >= input->bytesAvailable() ? input->bytesAvailable() : bytesRemaining;

        QByteArray chunk = input->read(chunkSize);

        mPayload.append(chunk);

        bytesRemaining -= chunk.size();
    }

    return bytesRemaining == 0 ? eSTATUS_OK : eSTATUS_INCOMPLETE;
}

bool RawMessage::readInt(qint32* value){
    if(mPayload.size() < sizeof(qint32)){
        return false;
    }

    QBuffer bfr(&mPayload);

    if(!bfr.open(QIODevice::ReadOnly)){
        return false;
    }

    if(bfr.read(reinterpret_cast<char*>(value), sizeof(qint32)) != sizeof(qint32)){
        return false;
    }

    *value = qFromBigEndian<qint32>(reinterpret_cast<uchar*>(value));

    return true;
}

void RawMessage::writeInt(qint32 value){
    quint32 beValue = qToBigEndian<quint32>(value);

    mPayload.append(reinterpret_cast<const char*>(&beValue), sizeof(quint32));
}

bool RawMessage::serialize(QIODevice* output) const{
    const_cast<RawMessage*>(this)->mLengthPrefix = 1 + mPayload.size();

    quint32 beLengthPrefix = qToBigEndian<quint32>(mLengthPrefix);

    if(output->write(reinterpret_cast<char*>(&beLengthPrefix), sizeof(quint32)) != sizeof(quint32)){
        qDebug() << "Error writing length prefix";

        return false;
    }

    if(!output->putChar(static_cast<char>(mId))){
        qDebug() << "Error writing message ID";

        return false;
    }

    if(mPayload.size() > 0){
        if(output->write(mPayload) != mPayload.size()){
            qDebug() << "Error writing payload";

            return false;
        }
    }

    return true;
}

quint32 RawMessage::getLengthPrefix() const{
    return mLengthPrefix;

}

RawMessage::Id RawMessage::getId() const{
    return mId;

}

const QByteArray& RawMessage::getPayload() const{
    return mPayload;
}

void RawMessage::setId(Id id){
    mId = id;
}

QByteArray& RawMessage::getPayload(){
    return mPayload;
}

} // bt

