#ifndef ZMQWORKERTHREAD_H
#define ZMQWORKERTHREAD_H

#include "message.pb.h"
#include "codeitem.h"
#include "telemetrybean.h"
#include <QObject>
#include <string>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <QThread>


class ZmqWorkerThread : public QObject
{
        Q_OBJECT
public:
    ZmqWorkerThread();
    void zmq_routine();
    void sendPacket(Telemetry *);
    void start();
signals:
    void callSelectCodeDialog(std::vector<CodeItem> codes);
    void refreshTelemetry(TelemetryBean state);
    void refreshConfig(std::string config);
private:
    boost::lockfree::queue<Telemetry *,boost::lockfree::capacity<50>> queue;
    boost::thread *_worker;
};

#endif // ZMQWORKERTHREAD_H
