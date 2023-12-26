#ifndef WEBSOCKETAPI_H
#define WEBSOCKETAPI_H

#include "../export.h"
#include <QObject>
#include "models/commandrequest.h"
#include "models/commandresult.h"
#include "models/objectrequest.h"
#include "models/objectresult.h"

class QWebSocket;

namespace WebSocketApiQt
{

class WebSocketServer;

class HTTP_SERVER_EXPORT WebSocketApi
{
    friend class WebSocketServer;
public:
    virtual ~WebSocketApi();

    virtual CommandResult onGetCommand(const CommandRequest &_req, QWebSocket *_socket) = 0;
    virtual ObjectResult onGetObject(const ObjectRequest &_req, QWebSocket *_socket) = 0;

    WebSocketServer *wsServer();

private:
    WebSocketServer *m_server;
};

}

#endif // WEBSOCKETAPI_H
