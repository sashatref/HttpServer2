#pragma once

#include "httprequesthandlerfactory.h"
#include "serveroptions.h"
#include "servermonitor.h"

namespace HttpServer2Qt
{

class ConnectionWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ConnectionWorker(qintptr _handle,
                     ServerMonitor *_monitor,
                     HttpRequestHandlerFactory *_factory,
                     const ServerOptions &_opt);

protected:
    virtual void run() override;

signals:
    void addStaticRequest();
    void addApiRequest();

private:
    QString checkForRedirect(const QString &_relPath);

    void writeJsonError(HttpRequestHandler *_handler,
                    HttpResponse *_response, HttpRequest *_req,
                    int _code,
                    const QString &_msg,
                    const QVariantMap &_userData = QVariantMap());

    qintptr m_handle;
    HttpRequestHandlerFactory *m_factory;

    ServerOptions m_opt;

    ServerMonitor *m_monitor;
};

}

