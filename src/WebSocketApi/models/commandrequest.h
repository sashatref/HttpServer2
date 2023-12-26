#ifndef COMMANDREQUEST_H
#define COMMANDREQUEST_H

#include "../../export.h"
#include "baserequest.h"

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT CommandRequest : public BaseRequest
{
public:
    QString commandName;    // имя команды

    CommandRequest();
};

}

#endif // COMMANDREQUEST_H
