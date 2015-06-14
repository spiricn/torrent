#ifndef TRACKERRESPONSE_H
#define TRACKERRESPONSE_H

#include <QDebug>

#include <be/Dictionary.h>

#include "bt/Global.h"
#include "bt/Peer.h"

namespace bt{

class BT_SHARED_EXPORT TrackerResponse{
public:
    TrackerResponse(be::DictionaryPtr dict);

    TrackerResponse();

    /**
     * Parses the dictionary containing the response.
     *
     * @return true if successfuly, false otherwise
     */
    bool parse();

    /**
     * Indicator wether or not the request has been successful.
     */
    bool isFailed() const;

    /**
     * Human-readable error message as to why the request failed
     *
     * @return Failure reason if it exists, empty string otherwise.
     */
    const QString& getFailureReason() const;

    /**
     * Similar to failure reason, but the response still gets
     * processed normally. The warning message is shown just like an error.
     *
     * @return Warning message if it exists, empty string otherwise.
     */
    const QString& getWarningMessage() const;

    /**
     * Interval in seconds that the client should wait between sending regular requests to the tracker
     *
     * @return Interval in seconds.
     */
    qint32 getInterval() const;

    /**
     * If present clients must not reannounce more frequently than this.
     *
     * @return Minimum interval in seconds if present, -1 otherwise
     */
    qint32 getMinInterval() const;

    /**
     * A string that the client should send back on its next announcements.
     * If absent and a previous announce sent a tracker id,
     * do not discard the old value; keep using it
     *
     * @return Tracker ID if it exists, empty string otherwise
     */
    const QString& getTrackerId() const;

    /**
     * Number of peers with the entire file, i.e. seeders.
     */
    qint32 getComplete() const;

    /**
     * Number of non-seeder peers, aka "leechers".
     */
    qint32 getIncomplete() const;

    const QList<Peer>& getPeers() const;

private:
    be::DictionaryPtr mDict;
    QString mFailureReason;
    QString mWarningMessage;
    qint32 mInterval;
    qint32 mMinInterval;
    QString mTrackerId;
    qint32 mComplete;
    qint32 mIncomplete;
    QList<Peer> mPeers;
};

} // bt

#endif // TRACKERRESPONSE_H

