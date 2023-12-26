#ifndef BASERESULT_H
#define BASERESULT_H

#include "../../export.h"
#include <QVariantMap>

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT BaseResult
{
public:
    int apiVer;         //версия API
    QVariantMap result; //возвращаемые результат
    int statusCode;     //код выполнения операции
    QString errMsg;     //текст ошибки

    BaseResult();
    virtual ~BaseResult();

    virtual void assignMap(QVariantMap &_m) const = 0;
};

}

#endif // BASERESULT_H
