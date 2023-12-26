#pragma once

#include "../export.h"
#include "ihandler.h"

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT ICommandHandler : public IHandler
{
    friend class RestApiHandler;
public:
    virtual void execute(QByteArray &_data, QByteArray &_contentType) = 0;
    virtual bool isRedirect(QString &_path);

    virtual QStringList allowedMethod() const;
};

}
