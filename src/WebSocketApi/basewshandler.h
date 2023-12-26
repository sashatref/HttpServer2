#ifndef BASEWSHANDLER_H
#define BASEWSHANDLER_H

#include "websocketapi.h"

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT BaseWSHandler : public WebSocketApi
{
public:
    using CommandFunc = std::function<CommandResult(const CommandRequest&, QWebSocket*)>;

    void registerCommand(const QString &_command, CommandFunc _func);

    template<class T>
    void registerCommand(const QString &_command,
                         T *_obj,
                         CommandResult(T::*func)(const CommandRequest&, QWebSocket*))
    {
        auto newFunc = std::bind(func, _obj, std::placeholders::_1, std::placeholders::_2);
        registerCommand(_command, newFunc);
    }

    virtual CommandResult onGetCommand(const CommandRequest &_req, QWebSocket *_socket) override;
    virtual ObjectResult onGetObject(const ObjectRequest &_req, QWebSocket *_socket) override;

private:
    QHash<QString, CommandFunc> m_commands;
};

}

#endif // BASEWSHANDLER_H
