#include "icommandhandler.h"

namespace HttpServer2Qt
{
bool ICommandHandler::isRedirect(QString &/*_path*/)
{
    return false;
}

QStringList ICommandHandler::allowedMethod() const
{
    return QStringList() << "POST";
}
}

