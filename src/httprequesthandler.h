#pragma once

#include "export.h"

namespace HttpServer2Qt
{

class HttpRequest;
class HttpResponse;

class HTTP_SERVER_EXPORT HttpRequestHandler : public QObject
{
    Q_OBJECT
public:
    HttpRequestHandler(QObject *_parent = nullptr);
    virtual ~HttpRequestHandler();

    virtual void handleRequest(HttpRequest *_req, HttpResponse *_res) = 0;

signals:
    void logData(const QVariantMap &_data, const QString &_type, QtMsgType _severity, const QString &_remoteIP);
};

}

