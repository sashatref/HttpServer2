#include "project_pch.h"
#include "websocketserver.h"
#include "websocketserverp.h"

namespace WebSocketApiQt
{

WebSocketServer::WebSocketServer(const QString &_name, int _port, QObject *_parent):
    QObject     (_parent),
    p           (new WebSocketServerP(_name, _port, this))
{
    connect(p, &WebSocketServerP::clientConnected, this, &WebSocketServer::clientConnected);
    connect(p, &WebSocketServerP::clientDisconneted, this, &WebSocketServer::clientDisconneted);
    connect(p, &WebSocketServerP::apiError, this, &WebSocketServer::apiError);
}

WebSocketServer::~WebSocketServer()
{

}

void WebSocketServer::setSslConfig(const QSslKey &_key, const QSslCertificate &_cert)
{
    p->setSslConfig(_key, _cert);
}

void WebSocketServer::setSslEnable(bool _isEnable)
{
    p->setSslEnable(_isEnable);
}

void WebSocketServer::setWebSocketApi(WebSocketApi *_api)
{
    p->setWebSocketApi(_api);
    _api->m_server = this;
}

void WebSocketServer::setName(const QString &_name)
{
    p->m_pWebSocketServer->setServerName(_name);
}

void WebSocketServer::setPort(int _port)
{
    p->m_port = _port;
}

void WebSocketServer::sendCommand(QWebSocket *_socket, const CommandResult &_command)
{
    QVariantMap out;
    _command.assignMap(out);

    out["actionOption"]     = "command";
    out["api"]              = 1;

    _socket->sendTextMessage(Text::writeToJson(out));
}

void WebSocketServer::sendCommandToAll(const CommandResult &_command)
{
    for(auto *sock : p->m_clients)
    {
        sendCommand(sock, _command);
    }
}

void WebSocketServer::start()
{
    p->start();
}

void WebSocketServer::stop()
{
    p->stop();
}


}
