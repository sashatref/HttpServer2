#ifndef WEBSOCKETSERVERP_H
#define WEBSOCKETSERVERP_H

#include "project_pch.h"
#include "models/commandrequest.h"
#include "models/commandresult.h"
#include "models/objectrequest.h"
#include "models/objectresult.h"
#include "websocketapi.h"

namespace WebSocketApiQt
{

class WebSocketServerP : public QObject
{
    Q_OBJECT
public:
    WebSocketServerP(const QString &_name, int _port, QObject *_p);
    ~WebSocketServerP();

    void setSslConfig(const QSslKey &_key, const QSslCertificate &_cert);
    void setSslEnable(bool _enable);

    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    WebSocketApi *m_wsApi;
    int m_port;
    QString m_name;

    void setWebSocketApi(WebSocketApi *_api);

signals:
    void apiError(const QString &_errMsg);
    void clientConnected(QWebSocket *_socket);
    void clientDisconneted(QWebSocket *_socket);

public slots:
    void start();
    void stop();

    void onNewConnection();
    void processTextMessage(const QString &message);
    void processBinaryMessage(const QByteArray &message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

    void textMessageReceivedSlot(const QString &_msg);
    void binaryMessageReceivedSlot(const QByteArray &_msg);
};

}

#endif // WEBSOCKETSERVERP_H
