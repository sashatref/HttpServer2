#include "utils.h"



QVariantMap Utils::parseCookies(const QString &_cookie)
{
    QVariantMap out;
    QStringList cookies = QString(_cookie).split(';');
    for(int i = 0 ; i < cookies.size(); i++)
    {
        QStringList keyValue = cookies.at(i).split('=');
        if(keyValue.size() < 2)
        {
            continue;
        }
        out[keyValue[0].trimmed()] = keyValue[1].trimmed();
    }

    return out;
}

bool Utils::findCookieListValue(const QString &_cookie, const QString &_valueToFind)
{
    QStringList encodingList = _cookie.split(",");

    for(const QString &enc : encodingList)
    {
        if(enc.compare(_valueToFind, Qt::CaseInsensitive) == 0)
        {
            return true;
        }
    }

    return false;
}

bool Utils::parseIsModifiedSinceHeader(const QMap<CIString, QString> &_headers, QString &_lastModified)
{
    const QString ifModifiedSince = "If-Modified-Since";

    if(!_headers.contains(ifModifiedSince))
    {
        return false;
    }

    _lastModified = _headers[ifModifiedSince];
    return true;
}

bool Utils::parseIsEtagHeader(const QMap<CIString, QString> &_headers, QString &_etag)
{
    const QString ifNoneMath = "If-None-Match";

    if(!_headers.contains(ifNoneMath))
    {
        return false;
    }

    _etag = _headers[ifNoneMath];
    return true;
}
