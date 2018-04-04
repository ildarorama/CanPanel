#include "zmqworkerthread.h"
#include "codeitem.h"
#include <zmq/zmq.hpp>
#include <iostream>
#include <vector>
#include <QDateTime>
#include <QDebug>

ZmqWorkerThread::ZmqWorkerThread() {
}

void ZmqWorkerThread::start() {
    _worker=new boost::thread(&ZmqWorkerThread::zmq_routine,this);
}

static void sendTelemetry(zmq::socket_t &s, Telemetry &t) {
    zmq::message_t m(t.ByteSize());

    if ( t.SerializeToArray(m.data(),m.size()) ) {
        std::cout << "Send telemetry " << RequestType_Name(t.type()) << std::endl;
        s.send(m,0);
    }
}

void ZmqWorkerThread::zmq_routine() {
    zmq::context_t c(3);
    zmq::socket_t s(c,zmq::socket_type::pair);
    int32_t seq=1;


    s.setsockopt(ZMQ_RCVTIMEO,30);
    s.connect("tcp://192.168.1.52:7777");

    Telemetry t;
    zmq::message_t recv_mess(10000);

    qint64 lastTimestamp=0;
    while(true) {
        t.Clear();
        qint64 timestamp=QDateTime::currentMSecsSinceEpoch();


        Telemetry *p=nullptr;
        if ( queue.pop(p) ) {
            p->set_seq(seq++);
            sendTelemetry(s,*p);
            delete p;
        }

        if ( (timestamp-lastTimestamp) > 1000 ) {
            qDebug() << lastTimestamp;
            lastTimestamp=timestamp;
            t.set_seq(seq);
            t.set_type(RequestType::TelemtryRequest);
            sendTelemetry(s,t);

            t.Clear();
            t.set_type(RequestType::Ping);
            t.set_seq(seq);
            sendTelemetry(s,t);
        }

        t.Clear();
        int r=s.recv(recv_mess.data(),recv_mess.size(),0);
        if (r>0) {
            if ( t.ParseFromArray(recv_mess.data(),r)) {

                std::cout << "Receive packet " << RequestType_Name(t.type()) << std::endl;


                if ( t.type() == RequestType::Ping ) {
                    t.set_type(RequestType::Pong);
                    t.set_seq(seq);
                    sendTelemetry(s,t);
                }

                if ( t.type() == RequestType::TelemetryResponse ) {



                   TelemetryBean s(
                               t.state().xcord(),
                               t.state().ycord(),
                               t.state().zcord(),
                               t.state().acord(),
                               t.state().bcord(),
                               t.state().ccord()
                               );
                   emit refreshTelemetry(s);
                }

                if ( t.type() == RequestType::ConfigResponse ) {
                   std::string conf=t.config().config();
                   emit refreshConfig(conf);
                }

                if ( t.type() == RequestType::CodeListResponse) {
                    int i=0;

                    std::vector<CodeItem> codes;
                    while(i<t.codelist_size()) {
                        Code c=t.codelist(i);
                        CodeItem item(c.name(),c.body());
                        codes.push_back(item);
                        i++;
                    }
                    emit callSelectCodeDialog(codes);
                }
            }
        }

    }
}



void ZmqWorkerThread::sendPacket(Telemetry *t) {
    queue.push(t);
}
