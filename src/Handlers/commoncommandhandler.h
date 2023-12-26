#pragma once

#include "../api/icommandhandler.h"
#include "../api/responceinfo.h"

namespace HttpServer2Qt
{

struct RequestData
{
    QByteArray contentType;
};

class HTTP_SERVER_EXPORT CommonCommandHandler : public ICommandHandler
{
    using Func = std::function<QByteArray(const ResponceInfo&, RequestData *)>;
public:
    CommonCommandHandler(Func _func);
    virtual void execute(QByteArray &_data, QByteArray &_contentType) override;

private:
    Func m_func;
};

}
