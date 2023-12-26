#pragma once

#include "../api/icommandhandler.h"

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT DataCommandHandler : public ICommandHandler
{
public:
    DataCommandHandler(const QByteArray &_data, const QByteArray &_contentType = "");

    virtual void execute(QByteArray &_data, QByteArray &_contentType) override;
    virtual QStringList allowedMethod() const override;

private:
    QByteArray m_data;
    QByteArray m_contentType;
};

}
