#include "bt/pwp/HandshakeMessage.h"

#define INFO_HASH_SIZE ( 20 )
#define PEER_ID_SIZE ( 20 )

namespace bt{

HandshakeMessage::HandshakeMessage(){
    memset(mReserved, 0x00, RESERVED_BYTES_SIZE);
}

HandshakeMessage::HandshakeMessage(const QByteArray& pstr, const QByteArray& infoHash, const QByteArray& peerId) : mPstr(pstr), mInfoHash(infoHash),
    mPeerId(peerId){
}

bool HandshakeMessage::serialize(QIODevice* output) const{
    // pstrlen
    if(!output->putChar(static_cast<char>(mPstr.size()))){
        return false;
    }

    // pstr
    if(output->write(mPstr) != mPstr.size()){
        return false;
    }

    // reserved
    for(int i=0; i<RESERVED_BYTES_SIZE; i++){
        if(!output->putChar(mReserved[i])){
            return false;
        }
    }

    // info_hash
    if(output->write(mInfoHash) != mInfoHash.size()){
        return false;
    }

    // peer_id
    if(output->write(mPeerId) != mPeerId.size()){
        return false;
    }

    return true;
}

IRawMessage::DeserializationStatus HandshakeMessage::deserialize(QIODevice* input){
    if(mPstr.size() == 0){
        if(input->bytesAvailable() < sizeof(char)){
            // Not enough bytes
            return eSTATUS_INCOMPLETE;
        }

        // pstrlen
        char pstrlen;
        if(!input->peek(&pstrlen, sizeof(char))){
            return eSTATUS_ERROR;
        }

        if(input->bytesAvailable() < static_cast<qint32>(sizeof(char) + pstrlen)){
            // Not enough bytes
            return eSTATUS_INCOMPLETE;
        }

        input->getChar(&pstrlen);

        // pstr
        mPstr = input->read(pstrlen);
    }

    static const qint32 remainingBytes = RESERVED_BYTES_SIZE + INFO_HASH_SIZE + PEER_ID_SIZE;

    if(input->bytesAvailable() < remainingBytes){
        return eSTATUS_INCOMPLETE;
    }

    // reserved
    if(input->read(mReserved, RESERVED_BYTES_SIZE) != RESERVED_BYTES_SIZE){
        return eSTATUS_ERROR;
    }

    // info_hash
    mInfoHash = input->read(INFO_HASH_SIZE);
    if(mInfoHash.size() != INFO_HASH_SIZE){
        return eSTATUS_ERROR;
    }

    // peer_id
    mPeerId = input->read(PEER_ID_SIZE);
    if(mPeerId.size() != PEER_ID_SIZE){
        return eSTATUS_ERROR;
    }

    return eSTATUS_OK;
}

const QByteArray& HandshakeMessage::getPstr() const{
    return mPstr;
}

const char* HandshakeMessage::getReserved() const{
    return mReserved;
}

const QByteArray& HandshakeMessage::getInfoHash() const{
    return mInfoHash;
}

const QByteArray& HandshakeMessage::getPeerId() const{
    return mPeerId;
}

} // bt
