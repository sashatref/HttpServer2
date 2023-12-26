#ifndef OBJECTREQUEST_H
#define OBJECTREQUEST_H

#include "../../export.h"
#include "baserequest.h"
#include "enums.h"

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT ObjectRequest : public BaseRequest
{
public:
    Enums::QueryType queryOption;       //тип запроса
    int indexOption;                    //передаваемый ID (-1 если не указан)
    QString objectName;                 //тип объекта

    ObjectRequest();
};

}

#endif // OBJECTREQUEST_H
