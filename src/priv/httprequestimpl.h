#pragma once

#include "../httprequest.h"

namespace HttpServer2Qt
{

class HttpRequestImpl : public HttpRequest
{
public:
    HttpRequestImpl(QAbstractSocket *_socket);

    // HttpRequest interface
public:
    virtual QString getMethod() const override;
    virtual void setUrl(const QUrl &_url) override;
    virtual QUrl getUrl() const override;
    virtual QHostAddress getClientAddress() const override;
    virtual QString getHttpVersion() const override;
    virtual QByteArray getRawData() const override;
    virtual const QMap<CIString, QString> &getHeaders() const override;
    virtual const QMap<CIString, QString> &getCookies() const override;

    virtual bool readHeaders() override;

    virtual QAbstractSocket *getSocket() override;

private:
    bool parseHeaders();
    bool parseCookies();

    QByteArray m_rawData;
    QUrl m_url;
    QString m_method;
    QString m_httpVersion;
    QHostAddress m_clientAddress;

    QMap<CIString, QString> m_headers;

    QMap<CIString, QString> m_cookies;

    QAbstractSocket *m_socket;
};

}
