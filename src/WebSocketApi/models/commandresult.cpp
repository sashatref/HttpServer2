#include "commandresult.h"

namespace WebSocketApiQt
{

CommandResult::CommandResult():
    commandName ()
{

}

void CommandResult::assignMap(QVariantMap &_m) const
{
    _m["result"]       = result;
    _m["statusCode"]   = statusCode;
    _m["errMsg"]       = errMsg;
    _m["commandName"]  = commandName;
}

}


