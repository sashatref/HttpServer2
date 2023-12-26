#include "objectresult.h"

namespace WebSocketApiQt
{

ObjectResult::ObjectResult():
    queryOption (),
    indexOption (-1),
    objectName  ()
{

}

void ObjectResult::assignMap(QVariantMap &_m) const
{
    _m["result"]       = result;
    _m["statusCode"]   = statusCode;
    _m["errMsg"]       = errMsg;
    _m["queryOption"]  = queryOption;
    _m["indexOption"]  = indexOption;
    _m["objectName"]   = objectName;
}

}


