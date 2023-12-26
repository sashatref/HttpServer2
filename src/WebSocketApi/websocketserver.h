#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include "../export.h"
#include "models/commandresult.h"
#include <QObject>

class QWebSocket;
class QSslKey;
class QSslCertificate;

namespace WebSocketApiQt
{

class WebSocketApi;
class WebSocketServerP;

class HTTP_SERVER_EXPORT WebSocketServer : public QObject
{
    Q_OBJECT
public:
    WebSocketServer(const QString &_name, int _port, QObject *_parent = 0);
    ~WebSocketServer();

    void setSslConfig(const QSslKey &_key, const QSslCertificate &_cert);
    void setSslEnable(bool _isEnable);

    void setWebSocketApi(WebSocketApi *_api);
    void setName(const QString &_name);
    void setPort(int _port);

    void sendCommand(QWebSocket *_socket, const CommandResult &_command);
    void sendCommandToAll(const CommandResult &_command);

public slots:
    void start();
    void stop();

signals:
    void apiError(const QString &_errMsg);
    void clientConnected(QWebSocket *_socket);
    void clientDisconneted(QWebSocket *_socket);

private:
    WebSocketServerP *p;
};

}

#endif // WEBSOCKETSERVER_H
