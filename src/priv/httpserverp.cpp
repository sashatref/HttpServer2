#include "httpserverp.h"
#include "asynctcpserver.h"
#include "httpserver.h"

namespace HttpServer2Qt
{

HttpServerP::HttpServerP(HttpServer *_q):
    QThread         (_q),
    q               (_q),
    m_tcpServer     (0)
{

}

HttpServerP::~HttpServerP()
{

}

void HttpServerP::run()
{
    if(m_tcpServer)
    {
        m_tcpServer->close();
        QThread::msleep(1000); // Время на освобождения ресурсов ОС
    }

    m_tcpServer.reset(new AsyncTcpServer(&m_monitor, m_factory, m_opt));

    m_tcpServer->setKey(m_opt.sslKey);
    m_tcpServer->setCert(m_opt.sslCertificate);
    m_tcpServer->setSslEnable(m_opt.sslEnabled);

    if(!m_tcpServer->listen(QHostAddress::Any, m_opt.port))
    {
        //qDebug() << "Error:" << m_tcpServer->errorString();
        emit message((tr("HTTP | Ошибка запуска сервера | %1")
                          .arg(m_tcpServer->errorString())), QtCriticalMsg);
        return;
    }

    //qDebug() << "TCP started";

    exec();

    m_tcpServer->close();
}



}
