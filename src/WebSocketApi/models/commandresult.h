#ifndef COMMANDRESULT_H
#define COMMANDRESULT_H

#include "../../export.h"
#include "baseresult.h"

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT CommandResult : public BaseResult
{
public:
    QString commandName;    //имя команды

    CommandResult();

    virtual void assignMap(QVariantMap &_m) const override;
};

}
#endif // COMMANDRESULT_H
