#include "asynctcpserver.h"
#include "connectionworker.h"

namespace HttpServer2Qt
{

AsyncTcpServer::AsyncTcpServer(ServerMonitor *_monitor,
                               HttpRequestHandlerFactory *_factory,
                               const ServerOptions &_opt,
                               QObject *_parent):
    QTcpServer  (_parent),
    m_factory   (_factory),
    m_serverOpt (_opt),
    m_monitor   (_monitor)
{
    m_pool.setMaxThreadCount(m_serverOpt.poolThreadCount);
}

AsyncTcpServer::~AsyncTcpServer()
{
    m_pool.waitForDone(1000);
}

void AsyncTcpServer::setMaxThreadCount(int _count)
{
    m_pool.setMaxThreadCount(_count);
}

void AsyncTcpServer::setKey(const QSslKey &_key)
{
    m_key = _key;
}

void AsyncTcpServer::setCert(const QSslCertificate &_cert)
{
    m_cert = _cert;
}

void AsyncTcpServer::setSslEnable(bool _sslEnable)
{
    m_sslEnable = _sslEnable;
}

void AsyncTcpServer::incomingConnection(qintptr handle)
{
    ConnectionWorker *worker = new ConnectionWorker(handle, m_monitor, m_factory, m_serverOpt);
    worker->setAutoDelete(true);
    m_pool.start(worker);
}

}
