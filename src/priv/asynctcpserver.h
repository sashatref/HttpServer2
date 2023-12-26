#pragma once

#include "httprequesthandlerfactory.h"
#include "serveroptions.h"
#include "servermonitor.h"

namespace HttpServer2Qt
{

class AsyncTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    AsyncTcpServer(ServerMonitor *_monitor, HttpRequestHandlerFactory *_factory, const ServerOptions &_opt, QObject *_parent = 0);
    ~AsyncTcpServer();
    void setMaxThreadCount(int _count);

    void setKey(const QSslKey &_key);
    void setCert(const QSslCertificate &_cert);
    void setSslEnable(bool _sslEnable);

protected:
    virtual void incomingConnection(qintptr handle) override;

private:
    QSslKey m_key;
    QSslCertificate m_cert;
    bool m_sslEnable = false;

    QThreadPool m_pool;
    HttpRequestHandlerFactory *m_factory = nullptr;

    ServerOptions m_serverOpt;
    ServerMonitor *m_monitor;
};

}
