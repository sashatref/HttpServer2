#include "basewshandler.h"

namespace WebSocketApiQt
{
void BaseWSHandler::registerCommand(const QString &_command, BaseWSHandler::CommandFunc _func)
{
    m_commands[_command] = _func;
}

CommandResult BaseWSHandler::onGetCommand(const CommandRequest &_req, QWebSocket *_socket)
{
    CommandResult res;

    auto it = m_commands.find(_req.commandName);
    if(it != m_commands.end())
    {
        res = it.value()(_req, _socket);
        res.commandName = _req.commandName;
    } else
    {
        qWarning() << QString("Command <%1> not supported").arg(_req.commandName);
    }

    return res;
}

ObjectResult BaseWSHandler::onGetObject(const ObjectRequest &/*_req*/, QWebSocket * /*_socket*/)
{
    ObjectResult res;
    return res;
}

}

