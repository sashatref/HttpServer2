#include "project_pch.h"
#include "httpserver.h"
#include "httpserverp.h"

namespace HttpServer2Qt
{

HttpServer::HttpServer(HttpRequestHandlerFactory *_factory, QObject *_parent):
        QObject     (_parent)
    {
        p = new HttpServerP(this);

        p->m_factory = _factory;
        connect(p, &HttpServerP::message, this, &HttpServer::message);
    }

    HttpServer::~HttpServer()
    {
        stop();

        delete p->m_factory;
    }

    void HttpServer::start()
    {
        p->start();
    }

    void HttpServer::stop()
    {
        p->quit();
        if(!p->wait(500))
        {
            p->terminate();
        }
    }

    void HttpServer::setPort(int _port)
    {
        p->m_opt.port = _port;
    }

    int HttpServer::getPort() const
    {
        return p->m_opt.port;
    }

    void HttpServer::setSslEnable(bool _enable)
    {
        p->m_opt.sslEnabled = _enable;
    }

    bool HttpServer::getSslEnable() const
    {
        return p->m_opt.sslEnabled;
    }

    void HttpServer::setServerOptions(const ServerOptions &_opt)
    {
        p->m_opt = _opt;
    }

    ServerOptions HttpServer::getServerOptions() const
    {
        return p->m_opt;
    }

    void HttpServer::setSslKey(const QSslKey &_key)
    {
        p->m_opt.sslKey = _key;
    }

    void HttpServer::setSslCert(const QSslCertificate &_cert)
    {
        p->m_opt.sslCertificate = _cert;
    }

    ServerMonitor *HttpServer::getServerMonitor()
    {
        return &p->m_monitor;
    }

}


