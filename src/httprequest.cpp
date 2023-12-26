#include "httprequest.h"
#include "priv/utils.h"

namespace HttpServer2Qt
{

const QString HttpRequest::HTTP_GET = "GET";
const QString HttpRequest::HTTP_HEAD = "HEAD";
const QString HttpRequest::HTTP_PUT = "PUT";
const QString HttpRequest::HTTP_POST = "POST";
const QString HttpRequest::HTTP_DELETE = "DELETE";

const QString HttpRequest::HOST = "Host";
const QString HttpRequest::COOKIE = "Cookie";
const QString HttpRequest::AUTHORIZATION = "Authorization";

HttpRequest::HttpRequest()
{

}

HttpRequest::HttpMethod HttpRequest::getMethodEnum() const
{
    static const QMap<QString, HttpMethod> m = {
        { "GET", GET_METHOD },
        { "POST", POST_METHOD },
        { "HEAD", HEAD_METHOD },
        { "PUT", PUT_METHOD },
        { "DELETE" , DELETE_METHOD }
    };

    QString method = getMethod();

    auto it = m.find(method);
    return it == m.end() ? UNKNOWN_METHOD : it.value();
}

QString HttpRequest::getUserAgent() const
{
    return getHeaders()["User-Agent"];
}

int HttpRequest::getContentLength() const
{
    return getHeaders()["Content-Length"].toInt();
}

QString HttpRequest::getContentType() const
{
    return getHeaders()["Content-Type"];
}

bool HttpRequest::hasClientGZipSupport() const
{
    return Utils::findCookieListValue(getHeaders()["Accept-Encoding"], "gzip");
}

QByteArray HttpRequest::readAllData()
{
    int totalSize = getContentLength();
    const int timeout = 30000;

    QByteArray out = getSocket()->readAll();

    while(out.size() < totalSize)
    {
        if(getSocket()->waitForReadyRead(timeout))
        {
            out.append(getSocket()->readAll());
        } else
        {
            break;
        }
    }

    return out;
}

}
