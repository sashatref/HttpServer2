#ifndef OBJECTRESULT_H
#define OBJECTRESULT_H

#include "../../export.h"
#include "baseresult.h"
#include "enums.h"

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT ObjectResult : public BaseResult
{
public:
    Enums::QueryType queryOption;       //тип запроса
    int indexOption;                    //передаваемый ID (-1 если не указан)
    QString objectName;                 //тип объекта

    ObjectResult();

    virtual void assignMap(QVariantMap &_m) const override;
};

}

#endif // OBJECTRESULT_H

