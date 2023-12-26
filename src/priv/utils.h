#pragma once

namespace Utils
{
    QVariantMap parseCookies(const QString &_cookie);

    //поиска значения в списке значений, разделенных запятой.
    //findCookieListValue("gzip, deflate, br", "gzip") => true
    bool findCookieListValue(const QString &_cookie, const QString &_valueToFind);

    bool parseIsModifiedSinceHeader(const QMap<CIString, QString> &_headers, QString &_lastModified);

    bool parseIsEtagHeader(const QMap<CIString, QString> &_headers, QString &_etag);
}

