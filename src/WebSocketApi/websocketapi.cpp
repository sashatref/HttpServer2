#include "websocketapi.h"

namespace WebSocketApiQt
{

WebSocketApi::~WebSocketApi()
{

}

WebSocketServer *WebSocketApi::wsServer()
{
    return m_server;
}


}
