#include "websocketserverp.h"

namespace WebSocketApiQt
{

WebSocketServerP::WebSocketServerP(const QString &_name, int _port, QObject *_p):
    QObject             (_p),
    m_pWebSocketServer  (0),
    m_clients           (),
    m_wsApi             (0),
    m_port              (_port),
    m_name              (_name)
{
    setSslEnable(false);
}

WebSocketServerP::~WebSocketServerP()
{
    stop();
    setWebSocketApi(0);
}

void WebSocketServerP::setSslConfig(const QSslKey &_key, const QSslCertificate &_cert)
{
    QSslConfiguration sslConfiguration;
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(_cert);
    sslConfiguration.setPrivateKey(_key);
    sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
    m_pWebSocketServer->setSslConfiguration(sslConfiguration);
}

void WebSocketServerP::setSslEnable(bool _enable)
{
    if(m_pWebSocketServer)
    {
        delete m_pWebSocketServer;
    }

    m_pWebSocketServer = new QWebSocketServer(m_name,
                                              _enable ? QWebSocketServer::SecureMode :
                                                        QWebSocketServer::NonSecureMode,
                                              this);

    connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
            this, &WebSocketServerP::onNewConnection);
    connect(m_pWebSocketServer, &QWebSocketServer::sslErrors,
            this, &WebSocketServerP::onSslErrors);
}

void WebSocketServerP::setWebSocketApi(WebSocketApi *_api)
{
    if(m_wsApi) delete m_wsApi;
    m_wsApi = _api;
}

void WebSocketServerP::start()
{
    if (!m_pWebSocketServer->listen(QHostAddress::Any, m_port))
    {
        throw UserExceptions::BaseException(tr("Ошибка запуска WebSocket сервера | %1")
                                            .arg(m_pWebSocketServer->errorString()));
    }
}

void WebSocketServerP::stop()
{
    for(auto &item : m_clients)
    {
        emit item->close();
    }

    m_pWebSocketServer->close();
}

void WebSocketServerP::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServerP::textMessageReceivedSlot);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServerP::binaryMessageReceivedSlot);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServerP::socketDisconnected);

    m_clients << pSocket;

    emit clientConnected(pSocket);
}

void WebSocketServerP::processTextMessage(const QString &message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        pClient->sendTextMessage(message);
    }
}

void WebSocketServerP::processBinaryMessage(const QByteArray &message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        pClient->sendBinaryMessage(message);
    }
}

void WebSocketServerP::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (pClient)
    {
        emit clientDisconneted(pClient);
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void WebSocketServerP::onSslErrors(const QList<QSslError> &/*errors*/)
{
    zWarning() << "Ssl errors occurred";
}

void WebSocketServerP::textMessageReceivedSlot(const QString &_msg)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (!pClient) return;

    QVariantMap m = Text::parseJson(_msg.toUtf8());
    QVariantMap out;

    const QString actionOptions = m["actionOption"].toString();
    out["actionOption"]     = m["actionOption"];
    out["api"]              = m["api"];

    if(actionOptions == "command")
    {
        CommandRequest req;
        req.apiVer          = m["api"].toInt();
        req.commandName     = m["commandName"].toString();
        req.value           = m["value"].toMap();

        CommandResult res = m_wsApi->onGetCommand(req, pClient);
        res.commandName = req.commandName;
        res.assignMap(out);
    } else if(actionOptions == "object")
    {
        ObjectRequest req;
        req.apiVer          = m["api"].toInt();
        req.indexOption     = m["indexOption"].toInt();
        req.objectName      = m["objectName"].toString();
        req.queryOption     = Enums::queryTypeFromString(m["queryOption"].toString());
        req.value           = m["value"].toMap();

        ObjectResult res = m_wsApi->onGetObject(req, pClient);
        res.objectName = req.objectName;
        res.queryOption = req.queryOption;
        res.indexOption = req.indexOption;
        res.assignMap(out);

    } else
    {
        const QString errMsg = tr("Action option <%1> not supported").arg(actionOptions);
        emit apiError(errMsg);

        out["apiVer"]           = m["apiVer"];
        out["actionOption"]     = m["actionOption"];
        out["indexOption"]      = m["indexOption"];
        out["objectName"]       = m["objectName"];
        out["queryOption"]      = m["queryOption"];
        out["statusCode"]       = 400;
        out["errMsg"]           = errMsg;
    }

    //qDebug() << pClient->isValid();
    pClient->sendTextMessage(Text::writeToJson(out));
}

void WebSocketServerP::binaryMessageReceivedSlot(const QByteArray &_msg)
{
    qDebug() << Q_FUNC_INFO << _msg;
    processBinaryMessage(_msg);

}

}
