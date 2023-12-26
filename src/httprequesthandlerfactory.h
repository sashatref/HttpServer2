#pragma once

#include "export.h"

namespace HttpServer2Qt
{

class HttpRequestHandler;
class HttpRequest;
class HttpResponse;

class HTTP_SERVER_EXPORT HttpRequestHandlerFactory : public QObject
{
    Q_OBJECT
public:
    virtual HttpRequestHandler* handleRequest(HttpRequest *_req, HttpResponse *_res) = 0;

    virtual ~HttpRequestHandlerFactory() = default;
};

}
