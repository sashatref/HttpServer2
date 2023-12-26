#pragma once

#include "../httprequesthandler.h"
#include "../export.h"

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT PhpHandler : public HttpRequestHandler
{
public:
    PhpHandler();

    virtual void handleRequest(HttpRequest *_req, HttpResponse *_res) override;

private:
    QString m_phpPath;
    int phpFileTimeout = 30000;
};

}

