#include "bt/pwp/PeerCommunication.h"

#include "bt/pwp/MessageChoke.h"
#include "bt/pwp/MessageUnchoke.h"
#include "bt/pwp/MessageInterested.h"
#include "bt/pwp/MessageNotIntereseted.h"
#include "bt/pwp/MessageHave.h"
#include "bt/pwp/MessageBitfield.h"
#include "bt/pwp/MessageRequest.h"
#include "bt/pwp/MessagePiece.h"
#include "bt/pwp/MessageCancel.h"
#include "bt/pwp/MessagePort.h"



#define PROTOCOL_IDENTIFIER "BitTorrent protocol"

namespace bt{

PeerCommunication::PeerCommunication(ITorrentManager* manager, PeerPtr peer, const MetaInfo& meta) : mManager(manager), mPeer(peer), mMeta(meta) {
    setState(eSTATE_DISCONNECTED);

    connect(&mSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&mSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&mSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    mSocket.connectToHost(peer->getIP(), peer->getPort());
}

void PeerCommunication::onConnected(){
    qDebug() << "Connected to peer";

    setState(eSTATE_HANDSHAKE);

    HandshakeMessage handshakeMessage(PROTOCOL_IDENTIFIER, mMeta.getInfo()->getInfoHash(), mManager->getPeerId());

    handshakeMessage.serialize(&mSocket);
}

void PeerCommunication::onDisconnected(){
    qDebug() << "Disconnected from peer";
}

void PeerCommunication::disconnect(){
    mSocket.close();

    emit connectionLost();
}

void PeerCommunication::onReadyRead(){
    if(mState == eSTATE_HANDSHAKE){
        // Handshake
        IRawMessage::DeserializationStatus status = mHandshakeMessage.deserialize(&mSocket);

        if(status == IRawMessage::eSTATUS_ERROR){
            qDebug() << "Error readigin handshake message";

            disconnect();

            return;
        }
        else if(status == IRawMessage::eSTATUS_OK){
            if(mHandshakeMessage.getInfoHash() != mMeta.getInfo()->getInfoHash()){
                qDebug() << "Handshake failed (info hash mismatch); closing connection";

                disconnect();

                return;
            }

            qDebug() << "Handshake successful";

            setState(eSTATE_MESSAGE);

            emit connectionEstablished();
        }
    }
    else if(mState == eSTATE_MESSAGE){
        if(mCurrentMessage == NULL){
            mCurrentMessage = RawMessagePtr(new RawMessage);
        }

        IRawMessage::DeserializationStatus status = mCurrentMessage->deserialize(&mSocket);

        if(status == IRawMessage::eSTATUS_OK){
            AMessage* message = NULL;

            switch(mCurrentMessage->getId()){
                case RawMessage::eID_CHOKE:
                    message = new MessageChoke();
                    break;
                case RawMessage::eID_UNCHOKE:
                    message = new MessageUnchoke();
                    break;
                case RawMessage::eID_INTERESTED:
                    message = new MessageInterested();
                    break;
                case RawMessage::eID_NOT_INTERESTED:
                    message = new MessageNotInterested();
                    break;
                case RawMessage::eID_HAVE:
                    message = new MessageHave();
                    break;
                case RawMessage::eID_BITFIELD:
                    message = new MessageBitfield();
                    break;
                case RawMessage::eID_REQUEST:
                    message = new MessageRequest();
                    break;
                case RawMessage::eID_PIECE:
                    message = new MessagePiece();
                    break;
                case RawMessage::eID_CANCEL:
                    message = new MessageCancel();
                    break;
                default:
                    qDebug() << "Unhandled message type";
            }

            if(message != NULL){
                if(!message->deserialize(mCurrentMessage)){
                    qDebug() << "Error deserializing message";
                }
                else{
                    emit messageReceived(AMessagePtr(message));
                }
            }

            mCurrentMessage = RawMessagePtr(NULL);
        }
        else if(status == IRawMessage::eSTATUS_ERROR){
            qDebug() << "Error reading message";

            disconnect();

            return;
        }
    }
}

void PeerCommunication::setState(State state){
    mState = state;
}

bool PeerCommunication::sendMessage(const AMessage& message){
    RawMessage rawMessage;

    if(!message.serialize(&rawMessage)){
        return false;
    }

    bool res = rawMessage.serialize(&mSocket);

    if(!res){
        qDebug() << "Error sending message";
    }

    return res;
}


} // bt

