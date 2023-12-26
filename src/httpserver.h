#pragma once

#include "export.h"
#include <QObject>


class QSslKey;
class QSslCertificate;


/*!
 * Класс Асинхронного многопоточного HTTP сервера с поддержкой SSL
 */

namespace HttpServer2Qt
{

class HttpHandler;
class HttpServerP;
class HttpRequestHandlerFactory;
class ServerOptions;
class ServerMonitor;

class HTTP_SERVER_EXPORT HttpServer : public QObject
{
    Q_OBJECT
public:
    HttpServer(HttpRequestHandlerFactory *_factory, QObject *_parent = nullptr);
    ~HttpServer();

    void start();
    void stop();

    void setPort(int _port);
    int getPort() const;

    void setSslEnable(bool _enable);
    bool getSslEnable() const;

    void setServerOptions(const ServerOptions &_opt);
    ServerOptions getServerOptions() const;

    void setSslKey(const QSslKey &_key);
    void setSslCert(const QSslCertificate &_cert);

    ServerMonitor *getServerMonitor();

signals:
    void message(const QString &_str, QtMsgType _type);

private:
    HttpServerP *p;
};

}

