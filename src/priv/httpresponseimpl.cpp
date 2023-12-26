#include "httpresponseimpl.h"

namespace HttpServer2Qt
{

HttpResponseImpl::HttpResponseImpl(QAbstractSocket *_sock, const ServerOptions &_opt):
    HttpResponse(_sock, _opt)
{

}

}
