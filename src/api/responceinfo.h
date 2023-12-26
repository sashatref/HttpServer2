#pragma once

#include "../export.h"
#include <HelperLibrary/cistring.h>

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT ResponceInfo
{
public:
    friend class RestApiHandler;

    const QVariantMap &getParams() const;

    const QMap<CIString, QString> &getCookies() const;
    const QMap<CIString, QString> &getHeaders() const;

    QString parseAuthToken() const;

    const QHostAddress &getClientAddress() const;

private:
    QHostAddress m_clientAddress;
    QVariantMap m_params;
    QMap<CIString, QString> m_cookies;
    QMap<CIString, QString> m_headers;
};

}
