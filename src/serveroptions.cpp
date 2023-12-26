#include "serveroptions.h"
#include "buildNumber.h"

namespace HttpServer2Qt
{

ServerOptions::ServerOptions():
    serverName      ("TSHttpServer2 " FULL_VER),
    poolThreadCount (60)
{

}

void ServerOptions::addToIndexRedirect()
{
    redirects << qMakePair(QRegExp("/"), QString("index.html"));
}

}
