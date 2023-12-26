#pragma once
#include "../httpresponse.h"

namespace HttpServer2Qt
{

class HttpResponseImpl : public HttpResponse
{
    Q_OBJECT
public:
    HttpResponseImpl(QAbstractSocket *_sock, const ServerOptions &_opt);
};

}

