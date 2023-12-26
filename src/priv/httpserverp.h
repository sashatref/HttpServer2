#pragma once

#include "httprequesthandlerfactory.h"
#include "serveroptions.h"
#include "servermonitor.h"


namespace HttpServer2Qt
{

class AsyncTcpServer;

class HttpServer;
class HttpServerP : public QThread
{
    Q_OBJECT
public:
    HttpServer *q;
    HttpRequestHandlerFactory *m_factory;

    HttpServerP(HttpServer *_q);
    ~HttpServerP();

    virtual void run() override;

    ServerMonitor m_monitor;

    ServerOptions m_opt;

signals:
    void message(const QString &_msg, QtMsgType _type);

private:
    QScopedPointer<AsyncTcpServer> m_tcpServer;
};

}

