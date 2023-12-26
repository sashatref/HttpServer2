#pragma once

#include "export.h"

#include <QUrl>
#include <QHostAddress>
#include <HelperLibrary/cistring.h>

class QAbstractSocket;

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT HttpRequest
{
public:
    HttpRequest();
    virtual ~HttpRequest() = default;

    enum HttpMethod
    {
        UNKNOWN_METHOD = -1,
        GET_METHOD,
        POST_METHOD,
        PUT_METHOD,
        DELETE_METHOD,
        HEAD_METHOD
    };

    static const QString HTTP_GET;
    static const QString HTTP_HEAD;
    static const QString HTTP_PUT;
    static const QString HTTP_POST;
    static const QString HTTP_DELETE;

    static const QString HOST;
    static const QString COOKIE;
    static const QString AUTHORIZATION;

    virtual QString getMethod() const = 0;
    HttpMethod getMethodEnum() const;

    virtual void setUrl(const QUrl &_url) = 0;
    virtual QUrl getUrl() const = 0;
    virtual QHostAddress getClientAddress() const = 0;

    virtual QByteArray getRawData() const = 0;
    virtual QString getHttpVersion() const = 0;

    QString getUserAgent() const;
    int getContentLength() const;
    QString getContentType() const;

    bool hasClientGZipSupport() const;

    QByteArray readAllData();

    virtual QAbstractSocket *getSocket() = 0;

    virtual const QMap<CIString, QString> &getHeaders() const = 0;
    virtual const QMap<CIString, QString> &getCookies() const = 0;

private:
    virtual bool readHeaders() = 0;
};

}



