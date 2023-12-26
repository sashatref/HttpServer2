#pragma once

#include <exception>
#include <QString>
#include <QVariantMap>
#include "export.h"

#include <HelperLibrary/Exceptions/userexception.h>

namespace HttpServer2Qt
{
class HTTP_SERVER_EXPORT HttpException : public HelperLibrary::UserExceptions::BaseException
{
public:
    HttpException(const QString &_text);
};

//ошибка в реализации алгоритмов со стороны сервера
class HTTP_SERVER_EXPORT HttpInternalException : public HttpException
{
public:
    HttpInternalException(const QString &_text);
};


//ошибка со стороны клиента (не все параметры или неправильные параметры)
class HTTP_SERVER_EXPORT HttpClientException : public HttpException
{
public:
    HttpClientException(const QString &_text);
};


//ошибка авторизации пользователя
class HTTP_SERVER_EXPORT HttpUnauthorizedException : public HttpException
{
public:
    HttpUnauthorizedException(const QString &_path, const QString &_text);

    QString getPath() const;

private:
    QString m_path;
};

//ошибка в url запроса к api
class HTTP_SERVER_EXPORT HttpNoMethodException : public HttpException
{
public:
    HttpNoMethodException(const QString &_text);
};

//ошибка в url запроса к api
class HTTP_SERVER_EXPORT HttpNoImplementedException : public HttpInternalException
{
public:
    HttpNoImplementedException(const QString &_methodName);
};

class HTTP_SERVER_EXPORT HttpNotFound : public HttpException
{
public:
    HttpNotFound(const QString &_text);
};

class HTTP_SERVER_EXPORT HttpUserError : public HttpException
{
public:
    HttpUserError(const QVariantMap &_data, int _httpCode, const QString &_text);

    int httpCode = 0;
    const QVariantMap data;
};

}




