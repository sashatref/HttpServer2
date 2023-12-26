#ifndef BASEREQUEST_H
#define BASEREQUEST_H

#include "../../export.h"
#include <QVariantMap>

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT BaseRequest
{
public:
    int apiVer;         //версия API
    QVariantMap value;  //передаваемые значения

    BaseRequest();
    virtual ~BaseRequest();
};

}

#endif // BASEREQUEST_H
